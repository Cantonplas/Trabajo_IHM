#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registerdialog.h"
#include "statsdialog.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QButtonGroup>
#include <QIcon>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPen>
#include <QApplication>
#include <QColorDialog>
#include <QPixmap>
#include <QPainter>
#include <QSvgRenderer>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>


MainWindow::MainWindow(User* currentUser, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_currentUser(currentUser)
    , m_currentMode(NONE)
{
    ui->setupUi(this);
    m_sessionStart = QDateTime::currentDateTime();

    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->viewport()->installEventFilter(this);

    m_answerGroup = new QButtonGroup(this);

    setupToolIcons();
    setupToolModes();

    loadChart();

    initSelectionList();
    showSelectionView();
}

MainWindow::~MainWindow()
{
    if (m_protractorItem) delete m_protractorItem;
    if (m_rulerItem) delete m_rulerItem;

    delete ui;
}


void MainWindow::showSelectionView()
{
    ui->stackedWidgetProblem->setCurrentIndex(0);
}

void MainWindow::showProblemView()
{
    ui->stackedWidgetProblem->setCurrentIndex(1);
}

void MainWindow::initSelectionList()
{
    if(m_currentUser){
        QPixmap pixmap = QPixmap::fromImage(m_currentUser->avatar());
        if (!pixmap.isNull()) {
            ui->btnAvatar->setIcon(QIcon(pixmap));
            ui->btnAvatar->setIconSize(QSize(32, 32));
        }
    }

    ui->listProblems->clear();

    ui->listProblems->setWordWrap(true);
    ui->listProblems->setTextElideMode(Qt::ElideNone);
    ui->listProblems->setResizeMode(QListView::Adjust);
    ui->listProblems->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listProblems->setSpacing(12);


    const auto &problems = Navigation::instance().problems();
    for (int i = 0; i < problems.size(); ++i) {
        QString labelText = QString("%1. %2").arg(i + 1).arg(problems[i].text());

        QListWidgetItem *item = new QListWidgetItem(labelText);
        item->setData(Qt::UserRole, i);
        ui->listProblems->addItem(item);
    }
}

void MainWindow::on_listProblems_itemClicked(QListWidgetItem *item)
{
    int index = item->data(Qt::UserRole).toInt();
    const auto &problems = Navigation::instance().problems();

    if (index >= 0 && index < problems.size()) {
        m_currentProblem = problems[index];
        setupProblemUI(index);
        showProblemView();
    }
}

void MainWindow::on_btnRandom_clicked()
{
    const auto &problems = Navigation::instance().problems();
    if (!problems.isEmpty()) {
        int randomIndex = QRandomGenerator::global()->bounded(problems.size());
        m_currentProblem = problems[randomIndex];
        setupProblemUI(randomIndex);
        showProblemView();
    }
}

void MainWindow::on_btnShowCoordinates_clicked(bool checked) {
}

void MainWindow::on_btnAvatar_clicked()
{
    QMenu menu(this);

    QAction* actionPhoto = menu.addAction("Cambiar foto de perfil");
    connect(actionPhoto, &QAction::triggered, this, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        "Seleccionar Imagen", "", "Imágenes (*.png *.jpg *.jpeg)");

        if (!fileName.isEmpty()) {
            QImage newImg(fileName);
            if (!newImg.isNull()) {
                QImage smallImg = newImg.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                m_currentUser->setAvatar(smallImg);
                Navigation::instance().updateUser(*m_currentUser);
                updateAvatarUI();
                QMessageBox::information(this, "Perfil", "Foto actualizada.");
            }
        }
    });

    QAction* actionProfile = menu.addAction("Modificar datos personales");
    connect(actionProfile, &QAction::triggered, this, [this]() {
        RegisterDialog dialog(m_currentUser, this);
        if (dialog.exec() == QDialog::Accepted) {
            updateAvatarUI();
        }
    });

    menu.addSeparator();
    QAction* actionStats = menu.addAction("Ver mis Estadísticas");
    connect(actionStats, &QAction::triggered, this, [this]() {
        StatsDialog dialog(m_currentUser, this);
        dialog.exec();
    });

    menu.addSeparator();
    QAction* actionLogout = menu.addAction("Cerrar Sesión");
    connect(actionLogout, &QAction::triggered, this, &MainWindow::on_btnLogout_clicked);

    menu.exec(ui->btnAvatar->mapToGlobal(QPoint(0, ui->btnAvatar->height())));
}

void MainWindow::updateAvatarUI() {
    QPixmap pixmap;
    if (!m_currentUser->avatar().isNull()) {
        pixmap = QPixmap::fromImage(m_currentUser->avatar());
    }

    if (pixmap.isNull()) {
        pixmap.load(":/resources/user_default.png");
    }

    if (!pixmap.isNull()) {
        ui->btnAvatar->setIcon(QIcon(pixmap));
        ui->btnAvatar->setIconSize(QSize(40, 40));
    }
}

void MainWindow::setupToolIcons()
{
    QSize iconSize(40, 40);

    QIcon pointIcon(":/resources/Punto.jpg");

    if (!pointIcon.isNull()) {
        ui->btnPunto->setIcon(pointIcon);
        ui->btnPunto->setIconSize(iconSize);
    } else {
        qDebug() << "Error: No se pudo cargar el icono Punto.jpg.";
    }
}

void MainWindow::setupToolModes()
{
    m_toolGroup = new QButtonGroup(this);
    m_toolGroup->setExclusive(true);

    m_toolGroup->addButton(ui->btnPunto);
    m_toolGroup->addButton(ui->btnDrawLine);
    m_toolGroup->addButton(ui->btnDrawArc);
    m_toolGroup->addButton(ui->btnAnnotateText);
    m_toolGroup->addButton(ui->btnProtractor);
    m_toolGroup->addButton(ui->btnRulerDistance);
    m_toolGroup->addButton(ui->btnEraser);
    m_toolGroup->addButton(ui->btnShowCoordinates);

    connect(m_toolGroup, &QButtonGroup::buttonToggled, this, &MainWindow::onToolModeToggled);
}


void MainWindow::showSvgTool(const QString &resourcePath, QGraphicsPixmapItem *&item)
{
    //COmpás
    if (resourcePath.contains("compass_leg")) {
        if (!m_compassItem) {
            QSvgRenderer renderer(resourcePath);
            QSize renderSize(10, 250);
            QPixmap pixmap(renderSize);
            pixmap.fill(Qt::transparent);
            QPainter painter(&pixmap);
            renderer.render(&painter);

            m_compassItem = new CompassItem(pixmap, &m_currentDrawingColor);
            m_scene->addItem(m_compassItem);

            QPointF center = ui->graphicsView->mapToScene(ui->graphicsView->viewport()->rect().center());
            m_compassItem->setPos(center);
        }
        m_compassItem->setVisible(true);
        return;
    }

    //regla y transporatodr:
    if (!item) {
        QSvgRenderer renderer(resourcePath);
        QSize renderSize = resourcePath.contains("ruler") ? QSize(1000, 80) : QSize(500, 500);

        QPixmap pixmap(renderSize);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        renderer.render(&painter);

        if (resourcePath.contains("ruler")) {
            m_rulerItem = new RulerItem(pixmap, &m_currentDrawingColor);
            item = m_rulerItem;
        } else {
            item = new QGraphicsPixmapItem(pixmap);
            item->setFlags(QGraphicsItem::ItemIsMovable |
                           QGraphicsItem::ItemSendsGeometryChanges);
            item->setFlag(QGraphicsItem::ItemIgnoresTransformations, false); // ✅ clave
            item->setTransformOriginPoint(item->boundingRect().center());
        }

        m_scene->addItem(item);
        QPointF center = ui->graphicsView->mapToScene(ui->graphicsView->viewport()->rect().center());
        item->setPos(center - QPointF(renderSize.width()/2, renderSize.height()/2));
    }
    item->setVisible(true);

}


void MainWindow::onToolModeToggled(QAbstractButton *button, bool checked)
{
    if (m_protractorItem) m_protractorItem->setVisible(false);
    if (m_rulerItem) m_rulerItem->setVisible(false);
    if (m_compassItem) m_compassItem->setVisible(false);

    // Si Juan cambia de herramienta, borramos las líneas de coordenadas anteriores
    if (m_hLine) { m_scene->removeItem(m_hLine); delete m_hLine; m_hLine = nullptr; }
    if (m_vLine) { m_scene->removeItem(m_vLine); delete m_vLine; m_vLine = nullptr; }

    m_currentMode = NONE;

    if (checked) {
        if (button == ui->btnPunto) {
            m_currentMode = POINT_MODE;
        } else if (button == ui->btnDrawLine) {
            m_currentMode = LINE_MODE;
        } else if (button == ui->btnAnnotateText) {
            m_currentMode = TEXT_MODE;
        } else if (button == ui->btnEraser) {
            m_currentMode = ERASER_MODE;
        } else if (button == ui->btnProtractor) {
            m_currentMode = PROTRACTOR_MODE;
            showSvgTool(":/resources/icons/transportador.svg", m_protractorItem);
        } else if (button == ui->btnRulerDistance) {
            m_currentMode = RULER_MODE;
            showSvgTool(":/resources/icons/ruler.svg", m_rulerItem);
        }
        // AÑADE ESTO:
        else if (button == ui->btnShowCoordinates) {
            m_currentMode = COORDINATES_MODE;
        }
        else if (button == ui->btnDrawArc) {
            m_currentMode = ARC_MODE;
            showSvgTool(":/resources/icons/compass_leg.svg", (QGraphicsPixmapItem*&)m_compassItem);
        }
    }
}

void MainWindow::on_btnClearMap_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmar Limpieza",
                                  "¿Está seguro de que desea limpiar todas las marcas?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QList<QGraphicsItem*> itemsToRemove;

        for (QGraphicsItem* item : m_scene->items()) {
            // Identificamos el mapa base
            bool isMapBase = (item == m_mapItem);

            bool isSvgTool = (item == m_protractorItem ||
                              item == m_rulerItem ||
                              item == m_compassItem);

            if (!isMapBase && !isSvgTool) {
                itemsToRemove.append(item);
            }
        }

        for (QGraphicsItem* item : itemsToRemove) {
            m_scene->removeItem(item);
            delete item;
        }

        if (m_toolGroup->checkedButton()) {
            m_toolGroup->checkedButton()->setChecked(false);
            m_currentMode = NONE;
        }
    }
}

void MainWindow::on_btnChangeColor_clicked()
{
    QColor newColor = QColorDialog::getColor(m_currentDrawingColor, this, "Seleccione el color para las marcas");

    if (newColor.isValid()) {
        m_currentDrawingColor = newColor;
        qDebug() << "Nuevo color seleccionado:" << m_currentDrawingColor.name();
    }
}

void MainWindow::loadChart()
{
    QPixmap pixmap(":/resources/carta_nautica.jpg");
    if (pixmap.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen del mapa.";
        return;
    }
    m_mapItem = m_scene->addPixmap(pixmap);
    m_mapItem->setZValue(0);

    m_scene->setSceneRect(pixmap.rect());
    ui->graphicsView->resetTransform();
    ui->graphicsView->scale(0.4, 0.4);
    ui->graphicsView->centerOn(m_mapItem->boundingRect().center());
}

void MainWindow::setupProblemUI(int index)
{
    ui->labelTitle->setText(QString("Problema #%1").arg(index + 1));

    ui->textProblemDescription->setText(m_currentProblem.text());

    QVector<Answer> answers = m_currentProblem.answers();

    QList<QAbstractButton*> buttons = m_answerGroup->buttons();
    for(QAbstractButton* button : buttons) {
        m_answerGroup->removeButton(button);
    }

    auto setupRadio = [&](QRadioButton* r, int i) {
        if (i < answers.size()) {
            r->setText(answers[i].text());
            r->setVisible(true);
            m_answerGroup->addButton(r, i);
        } else {
            r->setVisible(false);
        }
    };

    setupRadio(ui->radioAns1, 0);
    setupRadio(ui->radioAns2, 1);
    setupRadio(ui->radioAns3, 2);
    setupRadio(ui->radioAns4, 3);

    m_answerGroup->setExclusive(false);
    if(m_answerGroup->checkedButton())
        m_answerGroup->checkedButton()->setChecked(false);
    m_answerGroup->setExclusive(true);
}

void MainWindow::on_btnCheck_clicked()
{
    int id = m_answerGroup->checkedId();
    if(id == -1) {
        QMessageBox::warning(this, "Aviso", "Por favor selecciona una respuesta.");
        return;
    }

    QVector<Answer> answers = m_currentProblem.answers();
    if (id >= 0 && id < answers.size()) {
        bool isCorrect = answers[id].validity();

        if(isCorrect) {
            m_sessionHits++;
            QMessageBox::information(this, "¡Correcto!", "¡Has acertado la respuesta!");
        } else {
            m_sessionFaults++;
            QMessageBox::critical(this, "Incorrecto", "Esa no es la respuesta correcta.");
        }
    }
}

void MainWindow::saveCurrentSession()
{
    if (m_sessionHits == 0 && m_sessionFaults == 0) {
        return;
    }

    Session finalSession(m_sessionStart, m_sessionHits, m_sessionFaults);

    Navigation::instance().addSession(m_currentUser->nickName(), finalSession);

    qDebug() << "Sesión guardada:" << m_sessionHits << "aciertos," << m_sessionFaults << "fallos.";
}


void MainWindow::on_btnZoomIn_clicked()
{
    ui->graphicsView->scale(1.2, 1.2);
}

void MainWindow::on_btnZoomOut_clicked()
{
    ui->graphicsView->scale(1.0/1.2, 1.0/1.2);
}

void MainWindow::on_btnClose_clicked()
{
    showSelectionView();
}

void MainWindow::on_btnLogout_clicked()
{
    saveCurrentSession();
    QApplication::exit(1000);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveCurrentSession();

    QMainWindow::closeEvent(event);
}

void MainWindow::setDrawLineMode(bool enabled)
{
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj != ui->graphicsView->viewport())
        return QMainWindow::eventFilter(obj, event);

    // Solo eventos de ratón
    if (event->type() != QEvent::MouseButtonPress &&
        event->type() != QEvent::MouseMove &&
        event->type() != QEvent::MouseButtonRelease)
        return QMainWindow::eventFilter(obj, event);

    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    QPointF scenePos = ui->graphicsView->mapToScene(mouseEvent->pos());

    // Regla
    if (m_rulerItem && m_rulerItem->isVisible()) {
        if (ui->graphicsView->itemAt(mouseEvent->pos()) == m_rulerItem) {
            return false;
        }
    }

    // Compás
    if (m_compassItem && m_compassItem->isVisible()) {
        if (m_compassItem->contains(m_compassItem->mapFromScene(scenePos))) {
            return false;
        }
    }

    // Solo boton derecho para dibujar y editar

    if (!(mouseEvent->button() == Qt::RightButton ||
          (mouseEvent->buttons() & Qt::RightButton)))
        return false;

   // Punto
    if (m_currentMode == POINT_MODE &&
        event->type() == QEvent::MouseButtonPress) {

        qreal r = 3.0;
        QGraphicsEllipseItem *point =
            m_scene->addEllipse(scenePos.x() - r, scenePos.y() - r,
                                r * 2, r * 2,
                                QPen(Qt::transparent),
                                QBrush(m_currentDrawingColor));
        point->setZValue(10);
        return true;
    }

    //Linea
    if (m_currentMode == LINE_MODE) {

        if (event->type() == QEvent::MouseButtonPress) {
            m_lineStart = scenePos;
            m_currentLineItem = new QGraphicsLineItem(QLineF(scenePos, scenePos));
            m_currentLineItem->setPen(QPen(m_currentDrawingColor, 2));
            m_currentLineItem->setZValue(10);
            m_scene->addItem(m_currentLineItem);
            return true;
        }

        if (event->type() == QEvent::MouseMove && m_currentLineItem) {
            m_currentLineItem->setLine(QLineF(m_lineStart, scenePos));
            return true;
        }

        if (event->type() == QEvent::MouseButtonRelease) {
            m_currentLineItem = nullptr;
            return true;
        }
    }

    //Texto
    if (m_currentMode == TEXT_MODE &&
        event->type() == QEvent::MouseButtonPress) {

        bool ok = false;
        QString text = QInputDialog::getText(
            this,
            "Anotar texto",
            "Introduce el texto:",
            QLineEdit::Normal,
            "",
            &ok
            );

        text = text.trimmed();
        if (ok && !text.isEmpty()) {
            QGraphicsTextItem *txtItem =
                m_scene->addText(text, QFont("Arial", 14));
            txtItem->setDefaultTextColor(m_currentDrawingColor);
            txtItem->setPos(scenePos);
            txtItem->setZValue(10);
            txtItem->setFlags(QGraphicsItem::ItemIsMovable |
                              QGraphicsItem::ItemIsSelectable);
        }
        return true;
    }

    //Goma:
    if (m_currentMode == ERASER_MODE &&
        event->type() == QEvent::MouseButtonPress) {

        QList<QGraphicsItem*> items =
            m_scene->items(scenePos,
                           Qt::IntersectsItemShape,
                           Qt::DescendingOrder,
                           ui->graphicsView->transform());

        for (QGraphicsItem *it : items) {

            // No borrar mapa ni herramientas
            if (it == m_mapItem) continue;
            if (it == m_protractorItem) continue;
            if (it == m_rulerItem) continue;
            if (it == m_compassItem) continue;

            m_scene->removeItem(it);
            delete it;
            break; // solo uno
        }
        return true;
    }

    //Coordenadas
    if (m_currentMode == COORDINATES_MODE &&
        event->type() == QEvent::MouseButtonPress) {

        QRectF rect = m_scene->sceneRect();

        if (m_hLine) { m_scene->removeItem(m_hLine); delete m_hLine; }
        if (m_vLine) { m_scene->removeItem(m_vLine); delete m_vLine; }

        m_hLine = m_scene->addLine(rect.left(), scenePos.y(),
                                   rect.right(), scenePos.y(),
                                   QPen(m_currentDrawingColor, 1, Qt::DashLine));

        m_vLine = m_scene->addLine(scenePos.x(), rect.top(),
                                   scenePos.x(), rect.bottom(),
                                   QPen(m_currentDrawingColor, 1, Qt::DashLine));

        m_hLine->setZValue(15);
        m_vLine->setZValue(15);
        return true;
    }

    return false;
}

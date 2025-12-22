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
    // Tu lógica de coordenadas
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


// --- DENTRO DE mainwindow.cpp ---
void MainWindow::showSvgTool(const QString &resourcePath, QGraphicsPixmapItem *&item)
{
    if (!item) {
        QSvgRenderer renderer(resourcePath);
        QSize renderSize;

        if (resourcePath.contains("ruler.svg")) {
            renderSize = QSize(1000, 80);
        } else if (resourcePath.contains("transportador.svg")) {
            renderSize = QSize(500, 500);
        } else {
            renderSize = QSize(100, 100);
        }

        QPixmap pixmap(renderSize);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        renderer.render(&painter);

        // CREACIÓN ÚNICA: Decidimos qué objeto crear
        if (resourcePath.contains("ruler.svg")) {
            // CAMBIO AQUÍ: Pasamos &m_currentDrawingColor al constructor
            m_rulerItem = new RulerItem(pixmap, &m_currentDrawingColor);
            item = m_rulerItem;
        } else {
            item = new QGraphicsPixmapItem(pixmap);
            // El transportador suele preferirse con tamaño fijo, por eso dejamos este flag
            item->setFlags(QGraphicsItem::ItemIsMovable |
                           QGraphicsItem::ItemSendsGeometryChanges |
                           QGraphicsItem::ItemIgnoresTransformations);
        }

        m_scene->addItem(item);

        // Posicionamiento inicial en el centro de la vista
        QPointF center = ui->graphicsView->mapToScene(ui->graphicsView->viewport()->rect().center());
        item->setPos(center - QPointF(renderSize.width()/2, renderSize.height()/2));
    }

    item->setVisible(true);
}
// =========================================================================
// SLOTS PARA LA BARRA DE HERRAMIENTAS
// =========================================================================

void MainWindow::onToolModeToggled(QAbstractButton *button, bool checked)
{
    // Ocultar todas las herramientas arrastrables al cambiar de modo
    if (m_protractorItem) m_protractorItem->setVisible(false);
    if (m_rulerItem) m_rulerItem->setVisible(false);

    m_currentMode = NONE;

    if (checked) {
        if (button == ui->btnPunto) {
            m_currentMode = POINT_MODE;
        } else if (button == ui->btnDrawLine) {
            m_currentMode = LINE_MODE;
        } else if (button == ui->btnDrawArc) {
            m_currentMode = ARC_MODE;
        } else if (button == ui->btnAnnotateText) {
            m_currentMode = TEXT_MODE;
        } else if (button == ui->btnEraser) {
            m_currentMode = ERASER_MODE;
        }

        // 3.8/3.9: Mostrar/crear la herramienta SVG arrastrable (como PixmapItem)
        else if (button == ui->btnProtractor) {
            m_currentMode = PROTRACTOR_MODE;
            showSvgTool(":/resources/icons/transportador.svg", m_protractorItem);

        } else if (button == ui->btnRulerDistance) {
            m_currentMode = RULER_MODE;
            showSvgTool(":/resources/icons/ruler.svg", m_rulerItem);
        }
    }

    qDebug() << "Modo de Herramienta actual:" << m_currentMode;
}

void MainWindow::on_btnClearMap_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmar Limpieza",
                                  "¿Está seguro de que desea limpiar todas las marcas de la carta?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QList<QGraphicsItem*> itemsToRemove;

        for (QGraphicsItem* item : m_scene->items()) {

            // 1. Identificar el mapa base: Asumimos que es el único QGraphicsPixmapItem que NO es una herramienta.
            // Si el mapa base es el primer QGraphicsItem añadido, podemos asumir que es el primer elemento de la escena
            // o que es el único QGraphicsPixmapItem que no tiene las banderas de tool.

            // --- CÓDIGO CLAVE CORREGIDO ---

            bool isMapBase = (qgraphicsitem_cast<QGraphicsPixmapItem*>(item) != nullptr &&
                              item != m_protractorItem &&
                              item != m_rulerItem);

            bool isSvgTool = (item == m_protractorItem || item == m_rulerItem);

            // Si el ítem NO es el mapa base Y NO es una de las herramientas SVG, se ELIMINA.
            if (!isMapBase && !isSvgTool) {
                itemsToRemove.append(item);
            }
            // -----------------------------
        }

        for (QGraphicsItem* item : itemsToRemove) {
            m_scene->removeItem(item);
            delete item;
        }

        // Si hay un modo de herramienta activo, lo desactiva.
        if (m_toolGroup->checkedButton()) {
            m_toolGroup->checkedButton()->setChecked(false);
            m_currentMode = NONE;
        }

        qDebug() << "Carta limpiada (3.7).";
    }
}

void MainWindow::on_btnChangeColor_clicked()
{
    // ACTUALIZADO: Selector de color para la variable global m_currentDrawingColor
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
    QGraphicsPixmapItem *item = m_scene->addPixmap(pixmap);
    m_scene->setSceneRect(pixmap.rect());
    ui->graphicsView->scale(0.4, 0.4);
    ui->graphicsView->centerOn(item->boundingRect().center());
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
        // ---------------------------------------------------------
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
    // Solo filtramos eventos que vengan del área del mapa (viewport)
    if (obj == ui->graphicsView->viewport()) {

        // --- ARREGLO PARA LA REGLA ---
        // Si el evento es de ratón, verificamos si la regla está debajo del puntero.
        if (event->type() == QEvent::MouseButtonPress ||
            event->type() == QEvent::MouseMove ||
            event->type() == QEvent::MouseButtonRelease) {

            QMouseEvent *e = static_cast<QMouseEvent*>(event);

            // Si la regla existe y es visible...
            if (m_rulerItem && m_rulerItem->isVisible()) {
                // Buscamos qué hay exactamente bajo la posición del ratón
                QGraphicsItem *itemUnderMouse = ui->graphicsView->itemAt(e->pos());

                // Si lo que hay debajo es la regla, devolvemos 'false' para que el evento
                // NO sea filtrado y llegue directamente a la clase RulerItem.
                if (itemUnderMouse == m_rulerItem) {
                    return false;
                }
            }
        }

        // --- MODO PUNTO (BOTÓN DERECHO) ---
        if (m_currentMode == POINT_MODE) {
            if (event->type() == QEvent::MouseButtonPress) {
                auto *e = static_cast<QMouseEvent*>(event);
                if (e->button() == Qt::RightButton) {
                    QPointF scenePos = ui->graphicsView->mapToScene(e->pos());
                    qreal radius = 3.0;
                    QGraphicsEllipseItem *point = m_scene->addEllipse(
                        scenePos.x() - radius, scenePos.y() - radius,
                        radius * 2, radius * 2,
                        QPen(Qt::transparent),
                        QBrush(m_currentDrawingColor)
                        );
                    point->setZValue(10);
                    return true;
                }
            }
        }

        // --- LÓGICA DE DIBUJO (LÍNEA Y ARCO CON BOTÓN DERECHO) ---
        // Agrupamos los eventos de ratón para manejar el dibujo dinámico
        if (event->type() == QEvent::MouseButtonPress ||
            event->type() == QEvent::MouseMove ||
            event->type() == QEvent::MouseButtonRelease) {

            auto *e = static_cast<QMouseEvent*>(event);

            // Verificamos que se esté usando el botón derecho
            if (e->button() == Qt::RightButton || (e->buttons() & Qt::RightButton)) {
                QPointF scenePos = ui->graphicsView->mapToScene(e->pos());

                // 1. CLIC DEL RATÓN: INICIAR DIBUJO
                if (event->type() == QEvent::MouseButtonPress) {
                    if (m_currentMode == LINE_MODE) {
                        m_lineStart = scenePos;
                        m_currentLineItem = new QGraphicsLineItem(QLineF(m_lineStart, m_lineStart));
                        m_currentLineItem->setPen(QPen(m_currentDrawingColor, 2));
                        m_currentLineItem->setZValue(10);
                        m_scene->addItem(m_currentLineItem);
                        return true;
                    }
                    else if (m_currentMode == ARC_MODE) {
                        m_arcCenter = scenePos;
                        m_currentArcItem = new QGraphicsEllipseItem(m_arcCenter.x(), m_arcCenter.y(), 0, 0);
                        m_currentArcItem->setPen(QPen(m_currentDrawingColor, 2));
                        m_currentArcItem->setZValue(10);
                        m_scene->addItem(m_currentArcItem);
                        return true;
                    }
                }
                // 2. MOVIMIENTO DEL RATÓN: ACTUALIZAR DIBUJO EN TIEMPO REAL
                else if (event->type() == QEvent::MouseMove) {
                    if (m_currentMode == LINE_MODE && m_currentLineItem) {
                        m_currentLineItem->setLine(QLineF(m_lineStart, scenePos));
                        return true;
                    }
                    else if (m_currentMode == ARC_MODE && m_currentArcItem) {
                        qreal radius = QLineF(m_arcCenter, scenePos).length();
                        m_currentArcItem->setRect(m_arcCenter.x() - radius, m_arcCenter.y() - radius,
                                                  radius * 2, radius * 2);
                        return true;
                    }
                }
                // 3. SOLTAR EL BOTÓN: FINALIZAR DIBUJO
                else if (event->type() == QEvent::MouseButtonRelease) {
                    m_currentLineItem = nullptr;
                    m_currentArcItem = nullptr;
                    return true;
                }
            }
        }
    }

    // Para cualquier otro evento u otro objeto, llamamos al filtro base
    return QMainWindow::eventFilter(obj, event);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registerdialog.h" // Si vas a editar perfil
#include <QRandomGenerator> // Para el random
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QButtonGroup>
#include <QIcon>
#include <QMouseEvent> // NUEVO
#include <QKeyEvent> // NUEVO
#include <QPen> // NUEVO
#include <QApplication> F
#include <QColorDialog>
#include <QPixmap>
#include <QPainter>
#include <QSvgRenderer> // Necesario para la renderización

// =========================================================================
// CONSTRUCTOR / DESTRUCTOR
// =========================================================================

MainWindow::MainWindow(User* currentUser, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_currentUser(currentUser)
    , m_currentMode(NONE)
{
    ui->setupUi(this);

    // 1. Configurar Escena
    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->viewport()->installEventFilter(this);

    // 2. Configurar Grupos de Botones
    m_answerGroup = new QButtonGroup(this);
    // (Los botones de respuesta se añaden dinámicamente luego)

    // Configurar herramientas
    setupToolIcons();
    setupToolModes();

    // 3. Cargar el mapa
    loadChart();

    // 4. Inicializar panel derecho
    initSelectionList();
    showSelectionView(); // Empezar mostrando la lista
}

MainWindow::~MainWindow()
{
    if (m_protractorItem) delete m_protractorItem;
    if (m_rulerItem) delete m_rulerItem;

    delete ui;
}


void MainWindow::showSelectionView()
{
    // Muestra la página 0 del StackedWidget (La lista de problemas)
    ui->stackedWidgetProblem->setCurrentIndex(0);
}

void MainWindow::showProblemView()
{
    // Muestra la página 1 del StackedWidget (El detalle del problema)
    ui->stackedWidgetProblem->setCurrentIndex(1);
}

void MainWindow::initSelectionList()
{
    // 1. Configurar Avatar
    if(m_currentUser){
        QPixmap pixmap = QPixmap::fromImage(m_currentUser->avatar());
        if (!pixmap.isNull()) {
            ui->btnAvatar->setIcon(QIcon(pixmap));
            ui->btnAvatar->setIconSize(QSize(32, 32));
        }
    }

    // 2. Configurar Lista
    ui->listProblems->clear();

    // --- CONFIGURACIÓN PARA QUE EL TEXTO NO SE CORTE ---
    ui->listProblems->setWordWrap(true);                   // Permite saltos de línea
    ui->listProblems->setTextElideMode(Qt::ElideNone);     // Prohíbe poner "..." al final
    ui->listProblems->setResizeMode(QListView::Adjust);    // Se adapta si cambias el tamaño de ventana
    ui->listProblems->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // Scroll suave
    ui->listProblems->setSpacing(12);                      // Espacio entre problemas
    // ---------------------------------------------------

    const auto &problems = Navigation::instance().problems();
    for (int i = 0; i < problems.size(); ++i) {
        // IMPORTANTE: Aquí pasamos el texto COMPLETO (problems[i].text()), sin .left()
        QString labelText = QString("%1. %2").arg(i + 1).arg(problems[i].text());

        QListWidgetItem *item = new QListWidgetItem(labelText);
        item->setData(Qt::UserRole, i);
        ui->listProblems->addItem(item);
    }
}

// SLOT: Cuando seleccionan un problema de la lista
void MainWindow::on_listProblems_itemClicked(QListWidgetItem *item)
{
    int index = item->data(Qt::UserRole).toInt();
    const auto &problems = Navigation::instance().problems();

    if (index >= 0 && index < problems.size()) {
        m_currentProblem = problems[index];
        setupProblemUI(index); // <--- AQUI: Pasamos el 'index'
        showProblemView();
    }
}

// SLOT: Botón Random
void MainWindow::on_btnRandom_clicked()
{
    const auto &problems = Navigation::instance().problems();
    if (!problems.isEmpty()) {
        int randomIndex = QRandomGenerator::global()->bounded(problems.size());
        m_currentProblem = problems[randomIndex];
        setupProblemUI(randomIndex); // <--- AQUI: Pasamos el 'randomIndex'
        showProblemView();
    }
}

void MainWindow::on_btnShowCoordinates_clicked(bool checked) {
    // Tu lógica de coordenadas
}

// SLOT: Avatar (Opcional, si quieres editar perfil)
void MainWindow::on_btnAvatar_clicked()
{
    RegisterDialog dialog(m_currentUser, this);
    if (dialog.exec() == QDialog::Accepted) {
        // Actualizar el icono si cambió
        QPixmap pixmap = QPixmap::fromImage(m_currentUser->avatar());
        ui->btnAvatar->setIcon(QIcon(pixmap));
    }
}

// =========================================================================
// FUNCIONES DE INICIALIZACIÓN Y AUXILIARES
// =========================================================================

void MainWindow::setupToolIcons()
{
    QSize iconSize(40, 40);

    // Carga del icono Punto.jpg (para el botón btnDrawPoint)
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
    m_toolGroup->setExclusive(true); // Solo una herramienta activa a la vez

    m_toolGroup->addButton(ui->btnPunto);
    m_toolGroup->addButton(ui->btnDrawLine);
    m_toolGroup->addButton(ui->btnDrawArc);
    m_toolGroup->addButton(ui->btnAnnotateText);
    m_toolGroup->addButton(ui->btnProtractor);
    m_toolGroup->addButton(ui->btnRulerDistance);
    m_toolGroup->addButton(ui->btnEraser);
    m_toolGroup->addButton(ui->btnShowCoordinates); // Si es checkable

    // Conectar la señal de cambio de herramienta
    connect(m_toolGroup, &QButtonGroup::buttonToggled, this, &MainWindow::onToolModeToggled);
}

// mainwindow.cpp (Modificación dentro de showSvgTool)

void MainWindow::showSvgTool(const QString &resourcePath, QGraphicsPixmapItem *&item)
{
    if (!item) {
        QSvgRenderer renderer(resourcePath);

        // --- DEFINICIÓN DEL TAMAÑO DE RENDERIZADO ---
        QSize renderSize;

        // Definimos tamaños apropiados para cada utensilio
        if (resourcePath.contains("ruler.svg")) {
            // Ajustar para que se vea alargada (e.g., 280x60 o la proporción de tu SVG)
            renderSize = QSize(800, 60);
        } else if (resourcePath.contains("transportador.svg")) {
            // Mantener el transportador cuadrado o grande para la precisión angular
            renderSize = QSize(500, 500);
        } else {
            renderSize = QSize(100, 100); // Tamaño por defecto para otros elementos
        }

        QPixmap pixmap(renderSize);
        pixmap.fill(Qt::transparent);

        QPainter painter(&pixmap);
        // La renderización se ajusta automáticamente al tamaño del QPixmap (renderSize)
        renderer.render(&painter);

        // ... (el resto del código se mantiene)
        item = new QGraphicsPixmapItem(pixmap);
        item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges |
                       QGraphicsItem::ItemIgnoresTransformations);

        m_scene->addItem(item);

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
    QColor newColor = QColorDialog::getColor(Qt::red, this, "Seleccione el color para las marcas");

    if (newColor.isValid()) {
        qDebug() << "Nuevo color seleccionado:" << newColor.name();
    }
}

// =========================================================================
// CÓDIGO ORIGINAL (SIN MODIFICAR)
// =========================================================================

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
    // ELIMINAMOS ESTA LÍNEA QUE DABA EL ERROR:
    // int index = Navigation::instance().problems().indexOf(m_currentProblem);

    // Usamos directamente el 'index' que nos pasan
    ui->labelTitle->setText(QString("Problema #%1").arg(index + 1));

    // ... (El resto de la función se queda IGUAL) ...
    ui->textProblemDescription->setText(m_currentProblem.text());

    QVector<Answer> answers = m_currentProblem.answers();

    // Limpiar grupo previo
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
    // Verificar si hay selección
    int id = m_answerGroup->checkedId();
    if(id == -1) {
        QMessageBox::warning(this, "Aviso", "Por favor selecciona una respuesta.");
        return;
    }

    // Verificar si es correcta
    QVector<Answer> answers = m_currentProblem.answers();
    if (id >= 0 && id < answers.size()) {
        if(answers[id].validity()) {
            QMessageBox::information(this, "¡Correcto!", "¡Has acertado la respuesta!");
        } else {
            QMessageBox::critical(this, "Incorrecto", "Esa no es la respuesta correcta.");
        }
    }
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
    QApplication::exit(1000);
}
// =========================================================================
// CÓDIGO AÑADIDO: Lógica de Dibujo de Líneas (Basado en el profesor)
// =========================================================================

// Esta función es necesaria para implementar la lógica del filtro de eventos
// La mantenemos para compatibilidad si usas QAction toggled.
// En tu caso, la activación del modo se realiza en onToolModeToggled.
void MainWindow::setDrawLineMode(bool enabled)
{
    // Esta función no se usa directamente con tu sistema de botones,
    // pero la dejamos si se usa un QAction por separado.
    // La verdadera activación de modo ocurre en onToolModeToggled()

    // Si la función fuera usada, aquí se activaría el modo y el cursor:
    // m_drawLineMode = enabled;
    // if (m_drawLineMode) view->setCursor(Qt::CrossCursor);
    // else view->unsetCursor();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    // En tu implementación, 'obj' será ui->graphicsView->viewport()
    if (obj == ui->graphicsView->viewport()) {

        // Adaptación: Sustituimos m_drawLineMode por m_currentMode == LINE_MODE
        if (m_currentMode != LINE_MODE)
            return false; // No estamos en modo línea, dejamos que la vista lo gestione (e.g., arrastre)

        if (event->type() == QEvent::MouseButtonPress) {
            auto *e = static_cast<QMouseEvent*>(event);

            // Usar el botón derecho para iniciar la línea (como en el código del profesor)
            if (e->button() == Qt::RightButton) {
                QPointF scenePos = ui->graphicsView->mapToScene(e->pos());
                m_lineStart = scenePos; // Guardar punto de inicio

                // Usamos un QPen (debes definir el color actual de dibujo)
                QPen pen(Qt::red, 2); // Usamos un grosor menor para el dibujo final
                m_currentLineItem = new QGraphicsLineItem();

                m_currentLineItem->setZValue(10); // Aseguramos que esté por encima del mapa
                m_currentLineItem->setPen(pen);

                // Inicializamos la línea como un punto
                m_currentLineItem->setLine(QLineF(m_lineStart, m_lineStart));
                ui->graphicsView->scene()->addItem(m_currentLineItem);

                return true; // Consumimos el evento
            }
        }
        else if (event->type() == QEvent::MouseMove) {
            auto *e = static_cast<QMouseEvent*>(event);

            // Si el botón derecho está presionado Y tenemos un objeto de línea
            if (e->buttons() & Qt::RightButton && m_currentLineItem) {
                QPointF p2 = ui->graphicsView->mapToScene(e->pos());
                // Redibujar la línea continuamente hasta la posición actual del ratón
                m_currentLineItem->setLine(QLineF(m_lineStart, p2));
                return true;
            }
        }
        else if (event->type() == QEvent::MouseButtonRelease) {
            auto *e = static_cast<QMouseEvent*>(event);

            // Al soltar el botón derecho, la línea se finaliza
            if (e->button() == Qt::RightButton && m_currentLineItem) {
                // Aquí se podría guardar la línea final o validar la longitud
                m_currentLineItem = nullptr; // La línea ya está en la escena, solo liberamos el puntero temporal
                return true;
            }
        }
    }

    // Si el evento no fue manejado por nuestra lógica de dibujo, lo pasamos al padre
    return QMainWindow::eventFilter(obj, event);
}

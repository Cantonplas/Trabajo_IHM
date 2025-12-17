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
#include <QApplication> // NUEVO
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
    , m_currentUser(currentUser) // Guardamos usuario
    , m_currentMode(NONE)
// ... inicializadores ...
{
    ui->setupUi(this);

    // 1. Configuración básica de Escena
    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->viewport()->installEventFilter(this);
    ui->listProblems->setVisible(false);

    // 2. Configurar Grupos de Botones (igual que antes)
    m_answerGroup = new QButtonGroup(this);
    // ... añadir radio buttons ...
    setupToolIcons();
    setupToolModes();

    // 3. Cargar el mapa (se queda cargado al fondo)
    loadChart();

    m_blurEffect = new QGraphicsBlurEffect(this);
    m_blurEffect->setBlurRadius(15); // Nivel de borrosidad (0 a 100)

    // IMPORTANTE: Aplicar el efecto SOLO al contenedor del juego
    ui->gameContentContainer->setGraphicsEffect(m_blurEffect);

    // 5. Inicializar la UI del Overlay (Lista de problemas, avatar)
    initOverlayUI();

    // 6. Activar modo selección al inicio
    toggleSelectionMode(true);
}

MainWindow::~MainWindow()
{
    if (m_protractorItem) delete m_protractorItem;
    if (m_rulerItem) delete m_rulerItem;

    delete ui;
}

/*
// Mantiene el overlay centrado y del tamaño correcto
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    // Hacemos que el overlay ocupe todo el centro o lo centramos
    if (ui->selectionOverlay->isVisible()) {
        ui->selectionOverlay->resize(this->size());
        ui->selectionOverlay->move(0, 0);
    }
}*/

void MainWindow::initOverlayUI()
{
    // Cargar avatar
    if(m_currentUser){
        QPixmap pixmap = QPixmap::fromImage(m_currentUser->avatar());
        if (!pixmap.isNull()) {
            ui->btnAvatar->setIcon(QIcon(pixmap));
        }
    }

    // Cargar problemas en la lista (UI element que moviste al overlay)
    ui->listProblems->setWordWrap(true);
    ui->listProblems->setTextElideMode(Qt::ElideNone);
    ui->listProblems->setResizeMode(QListView::Adjust); // Ajustar al redimensionar
    ui->listProblems->setSpacing(5);

    // Limpiar y cargar problemas
    ui->listProblems->clear();
    const auto &problems = Navigation::instance().problems();

    for (int i = 0; i < problems.size(); ++i) {
        QListWidgetItem *item = new QListWidgetItem(problems[i].text());

        // Opcional: Dar un poco de altura extra si se ve muy apretado,
        // aunque con WordWrap suele calcularlo solo, a veces ayuda poner un SizeHint mínimo
        // item->setSizeHint(QSize(0, 50));

        item->setData(Qt::UserRole, i);

        ui->listProblems->addItem(item);
    }

    ui->listProblems->setVisible(false);
    ui->btnToggleList->setChecked(false);
    ui->btnToggleList->setText("Ver lista de problemas ▼");
}

void MainWindow::on_btnToggleList_toggled(bool checked)
{
    ui->listProblems->setVisible(checked);
    ui->btnToggleList->setText(checked ? "Ocultar lista ▲" : "Ver lista de problemas ▼");
}

void MainWindow::toggleSelectionMode(bool enable)
{
    if (enable) {
        // MOSTRAR SELECCIÓN
        ui->selectionOverlay->setVisible(true);
        ui->selectionOverlay->raise(); // Traer al frente
        m_blurEffect->setEnabled(true); // Activar borroso al fondo
        ui->gameContentContainer->setEnabled(false); // Desactivar clicks en el mapa
    } else {
        // MOSTRAR JUEGO
        ui->selectionOverlay->setVisible(false);
        m_blurEffect->setEnabled(false); // Quitar borroso
        ui->gameContentContainer->setEnabled(true); // Reactivar mapa
    }
}

// SLOT: Cuando seleccionan un problema de la lista
void MainWindow::on_listProblems_itemClicked(QListWidgetItem *item)
{
    int index = item->data(Qt::UserRole).toInt();
    const auto &problems = Navigation::instance().problems();

    if (index >= 0 && index < problems.size()) {
        m_currentProblem = problems[index]; // Asignar problema actual
        setupProblemUI(); // Cargar textos del problema en la UI del juego

        // OCULTAR la selección y mostrar el juego
        toggleSelectionMode(false);
    }
}

// SLOT: Botón Random
void MainWindow::on_btnRandom_clicked()
{
    const auto &problems = Navigation::instance().problems();
    if (!problems.isEmpty()) {
        int randomIndex = QRandomGenerator::global()->bounded(problems.size());
        m_currentProblem = problems[randomIndex];
        setupProblemUI();
        toggleSelectionMode(false);
    }
}

// SLOT: Avatar (Opcional, si quieres editar perfil)
void MainWindow::on_btnAvatar_clicked()
{
    // Reutilizas RegisterDialog
    RegisterDialog dialog(m_currentUser, this);
    if (dialog.exec() == QDialog::Accepted) {
        // Recargar icono
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
    // m_toolGroup gestiona la exclusividad de los botones chequeables
    m_toolGroup = new QButtonGroup(this);

    m_toolGroup->setExclusive(true);

    // Añadir todos los botones chequeables al grupo
    m_toolGroup->addButton(ui->btnPunto);
    m_toolGroup->addButton(ui->btnDrawLine);
    m_toolGroup->addButton(ui->btnDrawArc);
    m_toolGroup->addButton(ui->btnAnnotateText);
    m_toolGroup->addButton(ui->btnProtractor);
    m_toolGroup->addButton(ui->btnRulerDistance);
    m_toolGroup->addButton(ui->btnEraser);
    m_toolGroup->addButton(ui->btnShowCoordinates);

    // Conectar la señal de toggle a la slot genérica (Corrección de sobrecarga aplicada)
    connect(m_toolGroup,
            QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),
            this,
            &MainWindow::onToolModeToggled);
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
    QPixmap chart(":/resources/carta_nautica.jpg");

    if (chart.isNull()) {
        m_scene->addText("Error: No se pudo cargar la imagen de la carta náutica.\nVerifica resources.qrc");
    } else {
        m_scene->addPixmap(chart);
        m_scene->setSceneRect(chart.rect());

        ui->graphicsView->fitInView(m_scene->itemsBoundingRect(), Qt::KeepAspectRatio);

        double zoomFactor = 50;
        ui->graphicsView->scale(zoomFactor, zoomFactor);

        ui->graphicsView->centerOn(m_scene->itemsBoundingRect().center());
    }
}

void MainWindow::setupProblemUI()
{
    // 1. Poner el texto del problema
    ui->labelProblemText->setText(m_currentProblem.text());

    // 2. Obtener las respuestas
    QVector<Answer> answers = m_currentProblem.answers();

    // 3. Limpiar el grupo de botones anterior para evitar conflictos
    QList<QAbstractButton*> buttons = m_answerGroup->buttons();
    for(QAbstractButton* button : buttons) {
        m_answerGroup->removeButton(button);
    }

    // 4. Asignar texto y AÑADIR AL GRUPO CON ID (0, 1, 2, 3)
    if (answers.size() > 0) {
        ui->radioAns1->setText(answers[0].text());
        ui->radioAns1->setVisible(true);
        m_answerGroup->addButton(ui->radioAns1, 0); // ID 0
    } else ui->radioAns1->setVisible(false);

    if (answers.size() > 1) {
        ui->radioAns2->setText(answers[1].text());
        ui->radioAns2->setVisible(true);
        m_answerGroup->addButton(ui->radioAns2, 1); // ID 1
    } else ui->radioAns2->setVisible(false);

    if (answers.size() > 2) {
        ui->radioAns3->setText(answers[2].text());
        ui->radioAns3->setVisible(true);
        m_answerGroup->addButton(ui->radioAns3, 2); // ID 2
    } else ui->radioAns3->setVisible(false);

    if (answers.size() > 3) {
        ui->radioAns4->setText(answers[3].text());
        ui->radioAns4->setVisible(true);
        m_answerGroup->addButton(ui->radioAns4, 3); // ID 3
    } else ui->radioAns4->setVisible(false);

    // 5. Reiniciar selección (ninguno marcado)
    // El truco es poner setExclusive(false), desmarcar, y volver a true.
    m_answerGroup->setExclusive(false);
    if(m_answerGroup->checkedButton()) {
        m_answerGroup->checkedButton()->setChecked(false);
    }
    m_answerGroup->setExclusive(true);
}

#include <QMessageBox> // Asegúrate de tener este include arriba

void MainWindow::on_btnCheck_clicked()
{
    // 1. Verificar si hay algo seleccionado
    if(m_answerGroup->checkedId() == -1) {
        QMessageBox::warning(this, "Aviso", "Por favor selecciona una respuesta.");
        return;
    }

    // 2. Obtener el índice seleccionado (0, 1, 2 o 3)
    int selectedIndex = m_answerGroup->checkedId();

    // 3. Comprobar si es correcto usando los datos del problema
    // Asumimos que tu clase Answer tiene un método 'isCorrect()' o 'correct()'
    // Verifica en navtypes.h cómo se llama. Suele ser .valid o .correct

    QVector<Answer> answers = m_currentProblem.answers();
    bool isCorrect = false;

    // Protección por si el índice se sale del rango
    if(selectedIndex >= 0 && selectedIndex < answers.size()){
        // Aquí depende de tu clase Answer.
        // Si tu clase Answer tiene un booleano público 'valid':
        isCorrect = answers[selectedIndex].validity();

        // O SI ES UNA FUNCIÓN, usa: answers[selectedIndex].isValid() o similar.
    }

    if(isCorrect) {
        QMessageBox::information(this, "¡Correcto!", "¡Has acertado la respuesta!");
    } else {
        QMessageBox::critical(this, "Incorrecto", "Esa no es la respuesta correcta.");
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
    toggleSelectionMode(true);
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

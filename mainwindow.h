#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QButtonGroup>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QAbstractButton>
#include <QGraphicsItem>      // Clase base
#include <QGraphicsPixmapItem> // Clase que usaremos para las herramientas
#include "navtypes.h"
#include <QSvgRenderer>       // Necesario para cargar SVGs en el .cpp (aunque usemos PixmapItem)
#include "tool.h"

// =========================================================================
// DEFINICIÓN DE MODOS DE EDICIÓN
// =========================================================================
enum DrawMode {
    NONE,
    POINT_MODE,
    LINE_MODE,
    ARC_MODE,
    TEXT_MODE,
    PROTRACTOR_MODE,
    RULER_MODE,
    ERASER_MODE
};
// =========================================================================

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const Problem &problem, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots Originales
    void on_btnZoomIn_clicked();
    void on_btnZoomOut_clicked();
    void on_btnCheck_clicked();
    void on_btnClose_clicked();

    // Slots AÑADIDOS para los botones de acción
    void on_btnClearMap_clicked();      // 3.7 Limpiar la carta
    void on_btnChangeColor_clicked();   // 3.5 Cambiar el color

    // Slot AÑADIDO para manejar el estado de los botones chequeables (modos)
    void onToolModeToggled(QAbstractButton *button, bool checked);

    //Dibujo de lineas (click derecho)
    void setDrawLineMode(bool enabled);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    Problem m_currentProblem;
    QButtonGroup *m_answerGroup;

    // Variables AÑADIDAS para la lógica de herramientas
    DrawMode m_currentMode;                               // Modo de edición actual

    // Herramientas que heredan de QGraphicsItem (Usando QGraphicsPixmapItem renderizado)
    QGraphicsPixmapItem *m_protractorItem = nullptr;         // 3.8 Transportador
    QGraphicsPixmapItem *m_rulerItem = nullptr;              // 3.9 Regla/Distancia
    QButtonGroup *m_toolGroup = nullptr;                     // Grupo para la exclusividad de herramientas

    // Funciones Auxiliares
    void loadChart();
    void setupProblemUI();

    void setupToolIcons();      // Inicializa los iconos en C++ (si no están en el .ui)
    void setupToolModes();      // Configura QButtonGroup y las conexiones
    void showSvgTool(const QString &resourcePath, QGraphicsPixmapItem *&item); // Función auxiliar para mostrar herramientas

    //Dibujo de lineas
    QPointF m_lineStart;                     // Punto de inicio de la línea (coordenadas de la escena)
    QGraphicsLineItem *m_currentLineItem = nullptr; // Puntero a la línea que se está arrastrando

    // Sobrescribir eventFilter para capturar el ratón en la vista
    bool eventFilter(QObject *watched, QEvent *event) override;
};

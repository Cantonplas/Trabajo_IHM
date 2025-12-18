#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QButtonGroup>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QAbstractButton>
#include <QGraphicsItem>      // Clase base
#include <QGraphicsPixmapItem> // Clase que usaremos para las herramientas
#include "navtypes.h"
#include <QSvgRenderer>       // Necesario para cargar SVGs en el .cpp (aunque usemos PixmapItem)
#include "tool.h"
#include <QGraphicsBlurEffect> // IMPORTANTE: Para el efecto borroso
#include <QListWidgetItem>     // Para la lista
#include "navigation.h"        // Para acceder a los problemas
#include "tool.h"// =========================================================================
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
    explicit MainWindow(User* currentUser, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // --- HERRAMIENTAS Y MAPA ---
    void on_btnZoomIn_clicked();
    void on_btnZoomOut_clicked();
    void on_btnClearMap_clicked();
    void on_btnChangeColor_clicked();
    void onToolModeToggled(QAbstractButton *button, bool checked);
    void on_btnShowCoordinates_clicked(bool checked); // Asegúrate de tener este slot o borrarlo si no lo usas

    // --- PANEL DE PROBLEMAS (STACKED WIDGET) ---
    void on_listProblems_itemClicked(QListWidgetItem *item);
    void on_btnRandom_clicked();
    void on_btnCheck_clicked();
    void on_btnClose_clicked(); // Botón "Volver a la lista"

    // --- USUARIO ---
    void on_btnAvatar_clicked();
    void on_btnLogout_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    Problem m_currentProblem;
    User* m_currentUser;
    QButtonGroup *m_answerGroup;

    // --- HERRAMIENTAS DE DIBUJO ---
    DrawMode m_currentMode;
    QGraphicsPixmapItem *m_protractorItem = nullptr;
    QGraphicsPixmapItem *m_rulerItem = nullptr;
    QButtonGroup *m_toolGroup = nullptr;
    QPointF m_lineStart;
    QGraphicsLineItem *m_currentLineItem = nullptr;

    // --- FUNCIONES AUXILIARES ---
    void loadChart();
    void setupProblemUI(int index);;      // Rellena los datos del problema en la UI
    void initSelectionList();   // Inicializa la lista de problemas

    // Navegación del panel derecho
    void showSelectionView();   // Muestra la página 0 (Lista)
    void showProblemView();     // Muestra la página 1 (Problema)
    void setDrawLineMode(bool enabled);

    // Eventos
    bool eventFilter(QObject *watched, QEvent *event) override;
    void setupToolIcons();
    void setupToolModes();
    void showSvgTool(const QString &resourcePath, QGraphicsPixmapItem *&item);
};

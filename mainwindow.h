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
    // CAMBIO 1: El constructor ya no pide un "Problem", sino el "User"
    explicit MainWindow(User* currentUser, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // CAMBIO 2: Necesario para mantener el overlay centrado si cambias el tamaño de ventana
    //void resizeEvent(QResizeEvent *event) override;

private slots:
    // Slots existentes...
    void on_btnZoomIn_clicked();
    void on_btnZoomOut_clicked();
    void on_btnCheck_clicked();
    void on_btnClose_clicked();
    void on_btnClearMap_clicked();
    void on_btnChangeColor_clicked();
    void onToolModeToggled(QAbstractButton *button, bool checked);
    void setDrawLineMode(bool enabled);

    // NUEVOS SLOTS (Traídos de SelectionWindow)
    void on_listProblems_itemClicked(QListWidgetItem *item); // Al hacer clic en un problema
    void on_btnRandom_clicked(); // Botón aleatorio
    void on_btnAvatar_clicked(); // Para editar perfil (si tienes botón)
    void on_btnToggleList_toggled(bool checked);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    Problem m_currentProblem;
    User* m_currentUser; // Guardamos el usuario
    QButtonGroup *m_answerGroup;

    // Efecto de desenfoque
    QGraphicsBlurEffect *m_blurEffect;

    // Variables de herramientas (tus variables existentes)...
    DrawMode m_currentMode;
    QGraphicsPixmapItem *m_protractorItem = nullptr;
    QGraphicsPixmapItem *m_rulerItem = nullptr;
    QButtonGroup *m_toolGroup = nullptr;
    QPointF m_lineStart;
    QGraphicsLineItem *m_currentLineItem = nullptr;

    // Funciones Auxiliares
    void loadChart();
    void setupProblemUI(); // Actualiza la interfaz con el problema seleccionado

    // Funciones nuevas de inicialización
    void initOverlayUI();  // Configura la lista y avatar
    void toggleSelectionMode(bool enable); // Activa/Desactiva el modo selección (blur)

    // Event filter...
    bool eventFilter(QObject *watched, QEvent *event) override;

    // Herramientas visuales
    void setupToolIcons();
    void setupToolModes();
    void showSvgTool(const QString &resourcePath, QGraphicsPixmapItem *&item);
};

#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QButtonGroup>
#include "navtypes.h" // Asegúrate de que este header define 'Problem'

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Modificamos el constructor para recibir el Problema seleccionado
    explicit MainWindow(const Problem &problem, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnZoomIn_clicked();
    void on_btnZoomOut_clicked();
    void on_btnCheck_clicked();
    void on_btnClose_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    Problem m_currentProblem;
    QButtonGroup *m_answerGroup;

    void loadChart();
    void setupProblemUI();
};

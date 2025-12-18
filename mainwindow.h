#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QButtonGroup>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QAbstractButton>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "navtypes.h"
#include <QSvgRenderer>
#include "tool.h"
#include <QGraphicsBlurEffect>
#include <QListWidgetItem>
#include "navigation.h"
#include "statsdialog.h"
#include <QMenu>
#include <QDateTime>

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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(User* currentUser, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_btnZoomIn_clicked();
    void on_btnZoomOut_clicked();
    void on_btnClearMap_clicked();
    void on_btnChangeColor_clicked();
    void onToolModeToggled(QAbstractButton *button, bool checked);
    void on_btnShowCoordinates_clicked(bool checked);

    void on_listProblems_itemClicked(QListWidgetItem *item);
    void on_btnRandom_clicked();
    void on_btnCheck_clicked();
    void on_btnClose_clicked();

    void on_btnAvatar_clicked();
    void on_btnLogout_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    Problem m_currentProblem;
    User* m_currentUser;
    QButtonGroup *m_answerGroup;


    int m_sessionHits;
    int m_sessionFaults;
    QDateTime m_sessionStart;
    void saveCurrentSession();
    void updateAvatarUI();

    DrawMode m_currentMode;
    QGraphicsPixmapItem *m_protractorItem = nullptr;
    QGraphicsPixmapItem *m_rulerItem = nullptr;
    QButtonGroup *m_toolGroup = nullptr;
    QPointF m_lineStart;
    QGraphicsLineItem *m_currentLineItem = nullptr;

    void setDrawLineMode(bool enabled);
    void loadChart();
    void setupProblemUI(int index);
    void initSelectionList();

    void showSelectionView();
    void showProblemView();

    bool eventFilter(QObject *watched, QEvent *event) override;
    void setupToolIcons();
    void setupToolModes();
    void showSvgTool(const QString &resourcePath, QGraphicsPixmapItem *&item);
};

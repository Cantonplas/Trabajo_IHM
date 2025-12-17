/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_Main;
    QWidget *gameContentContainer;
    QHBoxLayout *horizontalLayout;
    QFrame *frameTools;
    QVBoxLayout *verticalLayoutTools;
    QLabel *labelDrawTitle;
    QPushButton *btnPunto;
    QPushButton *btnDrawLine;
    QPushButton *btnDrawArc;
    QPushButton *btnAnnotateText;
    QFrame *line_1;
    QLabel *labelMeasureTitle;
    QPushButton *btnProtractor;
    QPushButton *btnRulerDistance;
    QFrame *line_2;
    QPushButton *btnChangeColor;
    QPushButton *btnEraser;
    QPushButton *btnClearMap;
    QPushButton *btnShowCoordinates;
    QSpacerItem *verticalSpacerTools;
    QVBoxLayout *layoutMap;
    QHBoxLayout *layoutZoom;
    QLabel *lblZoomIcon;
    QPushButton *btnZoomIn;
    QPushButton *btnZoomOut;
    QSpacerItem *horizontalSpacer;
    QGraphicsView *graphicsView;
    QFrame *frameProblem;
    QVBoxLayout *verticalLayoutProblem;
    QLabel *labelTitle;
    QLabel *labelProblemText;
    QFrame *lineProblem;
    QRadioButton *radioAns1;
    QRadioButton *radioAns2;
    QRadioButton *radioAns3;
    QRadioButton *radioAns4;
    QSpacerItem *verticalSpacerProblem;
    QPushButton *btnCheck;
    QPushButton *btnClose;
    QWidget *selectionOverlay;
    QVBoxLayout *verticalLayoutOverlay;
    QHBoxLayout *horizontalLayoutTopBar;
    QSpacerItem *horizontalSpacerTop;
    QVBoxLayout *verticalLayoutUser;
    QPushButton *btnAvatar;
    QPushButton *btnLogout;
    QSpacerItem *verticalSpacerTop2;
    QPushButton *btnRandom;
    QPushButton *btnToggleList;
    QListWidget *listProblems;
    QSpacerItem *verticalSpacerBottom;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1024, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_Main = new QGridLayout(centralwidget);
        gridLayout_Main->setSpacing(0);
        gridLayout_Main->setObjectName("gridLayout_Main");
        gridLayout_Main->setContentsMargins(0, 0, 0, 0);
        gameContentContainer = new QWidget(centralwidget);
        gameContentContainer->setObjectName("gameContentContainer");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gameContentContainer->sizePolicy().hasHeightForWidth());
        gameContentContainer->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(gameContentContainer);
        horizontalLayout->setObjectName("horizontalLayout");
        frameTools = new QFrame(gameContentContainer);
        frameTools->setObjectName("frameTools");
        frameTools->setMinimumSize(QSize(80, 0));
        frameTools->setMaximumSize(QSize(80, 16777215));
        frameTools->setFrameShape(QFrame::StyledPanel);
        frameTools->setFrameShadow(QFrame::Raised);
        verticalLayoutTools = new QVBoxLayout(frameTools);
        verticalLayoutTools->setSpacing(5);
        verticalLayoutTools->setObjectName("verticalLayoutTools");
        verticalLayoutTools->setContentsMargins(5, 5, 5, 5);
        labelDrawTitle = new QLabel(frameTools);
        labelDrawTitle->setObjectName("labelDrawTitle");
        labelDrawTitle->setAlignment(Qt::AlignCenter);

        verticalLayoutTools->addWidget(labelDrawTitle);

        btnPunto = new QPushButton(frameTools);
        btnPunto->setObjectName("btnPunto");
        btnPunto->setMinimumSize(QSize(60, 60));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/punto.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnPunto->setIcon(icon);
        btnPunto->setCheckable(true);

        verticalLayoutTools->addWidget(btnPunto);

        btnDrawLine = new QPushButton(frameTools);
        btnDrawLine->setObjectName("btnDrawLine");
        btnDrawLine->setMinimumSize(QSize(60, 60));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/Linea_icon.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnDrawLine->setIcon(icon1);
        btnDrawLine->setIconSize(QSize(40, 40));
        btnDrawLine->setCheckable(true);

        verticalLayoutTools->addWidget(btnDrawLine);

        btnDrawArc = new QPushButton(frameTools);
        btnDrawArc->setObjectName("btnDrawArc");
        btnDrawArc->setMinimumSize(QSize(60, 60));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/compas_icon.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnDrawArc->setIcon(icon2);
        btnDrawArc->setIconSize(QSize(40, 40));
        btnDrawArc->setCheckable(true);

        verticalLayoutTools->addWidget(btnDrawArc);

        btnAnnotateText = new QPushButton(frameTools);
        btnAnnotateText->setObjectName("btnAnnotateText");
        btnAnnotateText->setMinimumSize(QSize(60, 60));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/icons/T.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnAnnotateText->setIcon(icon3);
        btnAnnotateText->setIconSize(QSize(40, 40));
        btnAnnotateText->setCheckable(true);

        verticalLayoutTools->addWidget(btnAnnotateText);

        line_1 = new QFrame(frameTools);
        line_1->setObjectName("line_1");
        line_1->setFrameShape(QFrame::Shape::HLine);
        line_1->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayoutTools->addWidget(line_1);

        labelMeasureTitle = new QLabel(frameTools);
        labelMeasureTitle->setObjectName("labelMeasureTitle");
        labelMeasureTitle->setAlignment(Qt::AlignCenter);

        verticalLayoutTools->addWidget(labelMeasureTitle);

        btnProtractor = new QPushButton(frameTools);
        btnProtractor->setObjectName("btnProtractor");
        btnProtractor->setMinimumSize(QSize(60, 60));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/icons/transportador.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnProtractor->setIcon(icon4);
        btnProtractor->setIconSize(QSize(40, 40));
        btnProtractor->setCheckable(true);

        verticalLayoutTools->addWidget(btnProtractor);

        btnRulerDistance = new QPushButton(frameTools);
        btnRulerDistance->setObjectName("btnRulerDistance");
        btnRulerDistance->setMinimumSize(QSize(60, 60));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/icons/ruler_icon.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnRulerDistance->setIcon(icon5);
        btnRulerDistance->setIconSize(QSize(40, 40));
        btnRulerDistance->setCheckable(true);

        verticalLayoutTools->addWidget(btnRulerDistance);

        line_2 = new QFrame(frameTools);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayoutTools->addWidget(line_2);

        btnChangeColor = new QPushButton(frameTools);
        btnChangeColor->setObjectName("btnChangeColor");
        btnChangeColor->setMinimumSize(QSize(60, 60));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/icons/colores.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnChangeColor->setIcon(icon6);
        btnChangeColor->setIconSize(QSize(40, 40));

        verticalLayoutTools->addWidget(btnChangeColor);

        btnEraser = new QPushButton(frameTools);
        btnEraser->setObjectName("btnEraser");
        btnEraser->setMinimumSize(QSize(60, 60));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/resources/icons/eraser.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnEraser->setIcon(icon7);
        btnEraser->setIconSize(QSize(40, 40));
        btnEraser->setCheckable(true);

        verticalLayoutTools->addWidget(btnEraser);

        btnClearMap = new QPushButton(frameTools);
        btnClearMap->setObjectName("btnClearMap");
        btnClearMap->setMinimumSize(QSize(60, 60));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/resources/icons/ocultar.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnClearMap->setIcon(icon8);
        btnClearMap->setIconSize(QSize(40, 40));

        verticalLayoutTools->addWidget(btnClearMap);

        btnShowCoordinates = new QPushButton(frameTools);
        btnShowCoordinates->setObjectName("btnShowCoordinates");
        btnShowCoordinates->setMinimumSize(QSize(60, 60));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/resources/icons/coordenadas.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnShowCoordinates->setIcon(icon9);
        btnShowCoordinates->setIconSize(QSize(40, 40));
        btnShowCoordinates->setCheckable(true);

        verticalLayoutTools->addWidget(btnShowCoordinates);

        verticalSpacerTools = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutTools->addItem(verticalSpacerTools);


        horizontalLayout->addWidget(frameTools);

        layoutMap = new QVBoxLayout();
        layoutMap->setObjectName("layoutMap");
        layoutZoom = new QHBoxLayout();
        layoutZoom->setObjectName("layoutZoom");
        lblZoomIcon = new QLabel(gameContentContainer);
        lblZoomIcon->setObjectName("lblZoomIcon");
        lblZoomIcon->setMaximumSize(QSize(30, 30));
        lblZoomIcon->setPixmap(QPixmap(QString::fromUtf8(":/lupa.jpg")));
        lblZoomIcon->setScaledContents(true);

        layoutZoom->addWidget(lblZoomIcon);

        btnZoomIn = new QPushButton(gameContentContainer);
        btnZoomIn->setObjectName("btnZoomIn");

        layoutZoom->addWidget(btnZoomIn);

        btnZoomOut = new QPushButton(gameContentContainer);
        btnZoomOut->setObjectName("btnZoomOut");

        layoutZoom->addWidget(btnZoomOut);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutZoom->addItem(horizontalSpacer);


        layoutMap->addLayout(layoutZoom);

        graphicsView = new QGraphicsView(gameContentContainer);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

        layoutMap->addWidget(graphicsView);


        horizontalLayout->addLayout(layoutMap);

        frameProblem = new QFrame(gameContentContainer);
        frameProblem->setObjectName("frameProblem");
        frameProblem->setMinimumSize(QSize(300, 0));
        frameProblem->setMaximumSize(QSize(300, 16777215));
        frameProblem->setFrameShape(QFrame::StyledPanel);
        frameProblem->setFrameShadow(QFrame::Raised);
        verticalLayoutProblem = new QVBoxLayout(frameProblem);
        verticalLayoutProblem->setObjectName("verticalLayoutProblem");
        labelTitle = new QLabel(frameProblem);
        labelTitle->setObjectName("labelTitle");
        QFont font;
        font.setBold(true);
        labelTitle->setFont(font);

        verticalLayoutProblem->addWidget(labelTitle);

        labelProblemText = new QLabel(frameProblem);
        labelProblemText->setObjectName("labelProblemText");
        labelProblemText->setWordWrap(true);

        verticalLayoutProblem->addWidget(labelProblemText);

        lineProblem = new QFrame(frameProblem);
        lineProblem->setObjectName("lineProblem");
        lineProblem->setFrameShape(QFrame::Shape::HLine);
        lineProblem->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayoutProblem->addWidget(lineProblem);

        radioAns1 = new QRadioButton(frameProblem);
        radioAns1->setObjectName("radioAns1");

        verticalLayoutProblem->addWidget(radioAns1);

        radioAns2 = new QRadioButton(frameProblem);
        radioAns2->setObjectName("radioAns2");

        verticalLayoutProblem->addWidget(radioAns2);

        radioAns3 = new QRadioButton(frameProblem);
        radioAns3->setObjectName("radioAns3");

        verticalLayoutProblem->addWidget(radioAns3);

        radioAns4 = new QRadioButton(frameProblem);
        radioAns4->setObjectName("radioAns4");

        verticalLayoutProblem->addWidget(radioAns4);

        verticalSpacerProblem = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutProblem->addItem(verticalSpacerProblem);

        btnCheck = new QPushButton(frameProblem);
        btnCheck->setObjectName("btnCheck");

        verticalLayoutProblem->addWidget(btnCheck);

        btnClose = new QPushButton(frameProblem);
        btnClose->setObjectName("btnClose");

        verticalLayoutProblem->addWidget(btnClose);


        horizontalLayout->addWidget(frameProblem);


        gridLayout_Main->addWidget(gameContentContainer, 0, 0, 1, 1);

        selectionOverlay = new QWidget(centralwidget);
        selectionOverlay->setObjectName("selectionOverlay");
        sizePolicy.setHeightForWidth(selectionOverlay->sizePolicy().hasHeightForWidth());
        selectionOverlay->setSizePolicy(sizePolicy);
        verticalLayoutOverlay = new QVBoxLayout(selectionOverlay);
        verticalLayoutOverlay->setObjectName("verticalLayoutOverlay");
        verticalLayoutOverlay->setContentsMargins(60, -1, 20, -1);
        horizontalLayoutTopBar = new QHBoxLayout();
        horizontalLayoutTopBar->setObjectName("horizontalLayoutTopBar");
        horizontalSpacerTop = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutTopBar->addItem(horizontalSpacerTop);

        verticalLayoutUser = new QVBoxLayout();
        verticalLayoutUser->setObjectName("verticalLayoutUser");
        btnAvatar = new QPushButton(selectionOverlay);
        btnAvatar->setObjectName("btnAvatar");
        btnAvatar->setMinimumSize(QSize(80, 80));
        btnAvatar->setMaximumSize(QSize(80, 80));
        btnAvatar->setIconSize(QSize(60, 60));
        btnAvatar->setFlat(true);

        verticalLayoutUser->addWidget(btnAvatar);

        btnLogout = new QPushButton(selectionOverlay);
        btnLogout->setObjectName("btnLogout");

        verticalLayoutUser->addWidget(btnLogout);


        horizontalLayoutTopBar->addLayout(verticalLayoutUser);


        verticalLayoutOverlay->addLayout(horizontalLayoutTopBar);

        verticalSpacerTop2 = new QSpacerItem(20, 100, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayoutOverlay->addItem(verticalSpacerTop2);

        btnRandom = new QPushButton(selectionOverlay);
        btnRandom->setObjectName("btnRandom");
        btnRandom->setMinimumSize(QSize(480, 50));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        btnRandom->setFont(font1);

        verticalLayoutOverlay->addWidget(btnRandom, 0, Qt::AlignLeft);

        btnToggleList = new QPushButton(selectionOverlay);
        btnToggleList->setObjectName("btnToggleList");
        btnToggleList->setMinimumSize(QSize(480, 40));
        btnToggleList->setCheckable(true);

        verticalLayoutOverlay->addWidget(btnToggleList, 0, Qt::AlignLeft);

        listProblems = new QListWidget(selectionOverlay);
        listProblems->setObjectName("listProblems");
        listProblems->setMinimumSize(QSize(480, 300));
        listProblems->setMaximumSize(QSize(700, 16777215));

        verticalLayoutOverlay->addWidget(listProblems, 0, Qt::AlignLeft);

        verticalSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutOverlay->addItem(verticalSpacerBottom);


        gridLayout_Main->addWidget(selectionOverlay, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Resoluci\303\263n de Problema", nullptr));
        labelDrawTitle->setText(QCoreApplication::translate("MainWindow", "Dibujo", nullptr));
#if QT_CONFIG(tooltip)
        btnPunto->setToolTip(QCoreApplication::translate("MainWindow", "Marcar un punto", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnDrawLine->setToolTip(QCoreApplication::translate("MainWindow", "Trazar l\303\255nea", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnDrawArc->setToolTip(QCoreApplication::translate("MainWindow", "Comp\303\241s", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnAnnotateText->setToolTip(QCoreApplication::translate("MainWindow", "Texto", nullptr));
#endif // QT_CONFIG(tooltip)
        labelMeasureTitle->setText(QCoreApplication::translate("MainWindow", "Medici\303\263n", nullptr));
#if QT_CONFIG(tooltip)
        btnProtractor->setToolTip(QCoreApplication::translate("MainWindow", "Transportador", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnRulerDistance->setToolTip(QCoreApplication::translate("MainWindow", "Regla", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnChangeColor->setToolTip(QCoreApplication::translate("MainWindow", "Color", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnEraser->setToolTip(QCoreApplication::translate("MainWindow", "Borrador", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnClearMap->setToolTip(QCoreApplication::translate("MainWindow", "Limpiar todo", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnShowCoordinates->setToolTip(QCoreApplication::translate("MainWindow", "Coordenadas", nullptr));
#endif // QT_CONFIG(tooltip)
        lblZoomIcon->setText(QString());
        btnZoomIn->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btnZoomOut->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        labelTitle->setText(QCoreApplication::translate("MainWindow", "Problema:", nullptr));
        labelProblemText->setText(QCoreApplication::translate("MainWindow", "Texto del problema aqu\303\255...", nullptr));
        radioAns1->setText(QCoreApplication::translate("MainWindow", "Opci\303\263n A", nullptr));
        radioAns2->setText(QCoreApplication::translate("MainWindow", "Opci\303\263n B", nullptr));
        radioAns3->setText(QCoreApplication::translate("MainWindow", "Opci\303\263n C", nullptr));
        radioAns4->setText(QCoreApplication::translate("MainWindow", "Opci\303\263n D", nullptr));
        btnCheck->setText(QCoreApplication::translate("MainWindow", "Comprobar Respuesta", nullptr));
        btnClose->setText(QCoreApplication::translate("MainWindow", "Volver a Selecci\303\263n", nullptr));
        selectionOverlay->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"#selectionOverlay {\n"
"    background-color: rgba(20, 30, 40, 220); \n"
"}\n"
"#selectionOverlay QLabel, #selectionOverlay QCheckBox {\n"
"    color: #ffffff;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"#selectionOverlay QListWidget {\n"
"    background-color: #f0f0f0;\n"
"    color: #000000;\n"
"    border: 2px solid #5da4d6;\n"
"    border-radius: 6px;\n"
"    font-size: 13px;\n"
"}\n"
"#selectionOverlay QPushButton {\n"
"    background-color: #3498db; \n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"#selectionOverlay QPushButton:hover {\n"
"    background-color: #5dade2;\n"
"}\n"
"#selectionOverlay QPushButton:pressed {\n"
"    background-color: #2980b9;\n"
"}\n"
"#selectionOverlay #btnAvatar {\n"
"    background-color: transparent;\n"
"    border: 2px solid white;\n"
"    border-radius: 40px; \n"
"}\n"
"       ", nullptr));
        btnAvatar->setText(QString());
        btnLogout->setText(QCoreApplication::translate("MainWindow", "Cerrar sesi\303\263n", nullptr));
        btnRandom->setText(QCoreApplication::translate("MainWindow", "\302\241Problema aleatorio!", nullptr));
        btnToggleList->setText(QCoreApplication::translate("MainWindow", "Ver lista de problemas \342\226\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

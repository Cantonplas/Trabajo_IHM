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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayoutMain;
    QFrame *frameTopBar;
    QHBoxLayout *horizontalLayoutTop;
    QLabel *labelAppName;
    QSpacerItem *horizontalSpacerTop;
    QPushButton *btnAvatar;
    QHBoxLayout *horizontalLayoutGame;
    QFrame *frameTools;
    QVBoxLayout *verticalLayoutTools;
    QPushButton *btnPunto;
    QPushButton *btnDrawLine;
    QPushButton *btnDrawArc;
    QPushButton *btnAnnotateText;
    QPushButton *btnProtractor;
    QPushButton *btnRulerDistance;
    QPushButton *btnChangeColor;
    QPushButton *btnEraser;
    QPushButton *btnClearMap;
    QPushButton *btnShowCoordinates;
    QSpacerItem *verticalSpacerTools;
    QVBoxLayout *layoutMap;
    QGraphicsView *graphicsView;
    QFrame *frameRightPanel;
    QVBoxLayout *verticalLayoutRight;
    QStackedWidget *stackedWidgetProblem;
    QWidget *pageSelection;
    QVBoxLayout *verticalLayoutSelection;
    QLabel *labelSelectTitle;
    QPushButton *btnRandom;
    QListWidget *listProblems;
    QWidget *pageProblem;
    QVBoxLayout *verticalLayoutProblem;
    QLabel *labelTitle;
    QTextBrowser *textProblemDescription;
    QFrame *lineProblem;
    QRadioButton *radioAns1;
    QRadioButton *radioAns2;
    QRadioButton *radioAns3;
    QRadioButton *radioAns4;
    QSpacerItem *verticalSpacerProblem;
    QPushButton *btnCheck;
    QPushButton *btnClose;
    QHBoxLayout *layoutLogout;
    QPushButton *btnLogout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 850);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutMain = new QVBoxLayout(centralwidget);
        verticalLayoutMain->setSpacing(0);
        verticalLayoutMain->setObjectName("verticalLayoutMain");
        verticalLayoutMain->setContentsMargins(0, 0, 0, 0);
        frameTopBar = new QFrame(centralwidget);
        frameTopBar->setObjectName("frameTopBar");
        frameTopBar->setMinimumSize(QSize(0, 50));
        frameTopBar->setFrameShape(QFrame::StyledPanel);
        frameTopBar->setFrameShadow(QFrame::Raised);
        horizontalLayoutTop = new QHBoxLayout(frameTopBar);
        horizontalLayoutTop->setObjectName("horizontalLayoutTop");
        horizontalLayoutTop->setContentsMargins(15, 5, 15, 5);
        labelAppName = new QLabel(frameTopBar);
        labelAppName->setObjectName("labelAppName");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(12);
        font.setBold(true);
        labelAppName->setFont(font);

        horizontalLayoutTop->addWidget(labelAppName);

        horizontalSpacerTop = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutTop->addItem(horizontalSpacerTop);

        btnAvatar = new QPushButton(frameTopBar);
        btnAvatar->setObjectName("btnAvatar");
        btnAvatar->setMinimumSize(QSize(40, 40));
        btnAvatar->setMaximumSize(QSize(40, 40));
        btnAvatar->setIconSize(QSize(32, 32));
        btnAvatar->setFlat(true);

        horizontalLayoutTop->addWidget(btnAvatar);


        verticalLayoutMain->addWidget(frameTopBar);

        horizontalLayoutGame = new QHBoxLayout();
        horizontalLayoutGame->setSpacing(0);
        horizontalLayoutGame->setObjectName("horizontalLayoutGame");
        frameTools = new QFrame(centralwidget);
        frameTools->setObjectName("frameTools");
        frameTools->setMinimumSize(QSize(70, 0));
        frameTools->setMaximumSize(QSize(70, 16777215));
        frameTools->setFrameShape(QFrame::StyledPanel);
        frameTools->setFrameShadow(QFrame::Raised);
        verticalLayoutTools = new QVBoxLayout(frameTools);
        verticalLayoutTools->setSpacing(6);
        verticalLayoutTools->setObjectName("verticalLayoutTools");
        verticalLayoutTools->setContentsMargins(5, 10, 5, 10);
        btnPunto = new QPushButton(frameTools);
        btnPunto->setObjectName("btnPunto");
        btnPunto->setMinimumSize(QSize(50, 50));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/punto.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnPunto->setIcon(icon);
        btnPunto->setCheckable(true);

        verticalLayoutTools->addWidget(btnPunto);

        btnDrawLine = new QPushButton(frameTools);
        btnDrawLine->setObjectName("btnDrawLine");
        btnDrawLine->setMinimumSize(QSize(50, 50));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/Linea_icon.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnDrawLine->setIcon(icon1);
        btnDrawLine->setCheckable(true);

        verticalLayoutTools->addWidget(btnDrawLine);

        btnDrawArc = new QPushButton(frameTools);
        btnDrawArc->setObjectName("btnDrawArc");
        btnDrawArc->setMinimumSize(QSize(50, 50));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/compas_icon.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnDrawArc->setIcon(icon2);
        btnDrawArc->setCheckable(true);

        verticalLayoutTools->addWidget(btnDrawArc);

        btnAnnotateText = new QPushButton(frameTools);
        btnAnnotateText->setObjectName("btnAnnotateText");
        btnAnnotateText->setMinimumSize(QSize(50, 50));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/icons/T.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnAnnotateText->setIcon(icon3);
        btnAnnotateText->setCheckable(true);

        verticalLayoutTools->addWidget(btnAnnotateText);

        btnProtractor = new QPushButton(frameTools);
        btnProtractor->setObjectName("btnProtractor");
        btnProtractor->setMinimumSize(QSize(50, 50));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/icons/transportador.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnProtractor->setIcon(icon4);
        btnProtractor->setCheckable(true);

        verticalLayoutTools->addWidget(btnProtractor);

        btnRulerDistance = new QPushButton(frameTools);
        btnRulerDistance->setObjectName("btnRulerDistance");
        btnRulerDistance->setMinimumSize(QSize(50, 50));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/icons/ruler_icon.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnRulerDistance->setIcon(icon5);
        btnRulerDistance->setCheckable(true);

        verticalLayoutTools->addWidget(btnRulerDistance);

        btnChangeColor = new QPushButton(frameTools);
        btnChangeColor->setObjectName("btnChangeColor");
        btnChangeColor->setMinimumSize(QSize(50, 50));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/icons/colores.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnChangeColor->setIcon(icon6);

        verticalLayoutTools->addWidget(btnChangeColor);

        btnEraser = new QPushButton(frameTools);
        btnEraser->setObjectName("btnEraser");
        btnEraser->setMinimumSize(QSize(50, 50));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/resources/icons/eraser.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnEraser->setIcon(icon7);
        btnEraser->setCheckable(true);

        verticalLayoutTools->addWidget(btnEraser);

        btnClearMap = new QPushButton(frameTools);
        btnClearMap->setObjectName("btnClearMap");
        btnClearMap->setMinimumSize(QSize(50, 50));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/resources/icons/ocultar.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnClearMap->setIcon(icon8);

        verticalLayoutTools->addWidget(btnClearMap);

        btnShowCoordinates = new QPushButton(frameTools);
        btnShowCoordinates->setObjectName("btnShowCoordinates");
        btnShowCoordinates->setMinimumSize(QSize(50, 50));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/resources/icons/coordenadas.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnShowCoordinates->setIcon(icon9);
        btnShowCoordinates->setCheckable(true);

        verticalLayoutTools->addWidget(btnShowCoordinates);

        verticalSpacerTools = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutTools->addItem(verticalSpacerTools);


        horizontalLayoutGame->addWidget(frameTools);

        layoutMap = new QVBoxLayout();
        layoutMap->setObjectName("layoutMap");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

        layoutMap->addWidget(graphicsView);


        horizontalLayoutGame->addLayout(layoutMap);

        frameRightPanel = new QFrame(centralwidget);
        frameRightPanel->setObjectName("frameRightPanel");
        frameRightPanel->setMinimumSize(QSize(320, 0));
        frameRightPanel->setMaximumSize(QSize(350, 16777215));
        frameRightPanel->setFrameShape(QFrame::StyledPanel);
        frameRightPanel->setFrameShadow(QFrame::Raised);
        verticalLayoutRight = new QVBoxLayout(frameRightPanel);
        verticalLayoutRight->setObjectName("verticalLayoutRight");
        verticalLayoutRight->setContentsMargins(0, 0, 0, 10);
        stackedWidgetProblem = new QStackedWidget(frameRightPanel);
        stackedWidgetProblem->setObjectName("stackedWidgetProblem");
        pageSelection = new QWidget();
        pageSelection->setObjectName("pageSelection");
        verticalLayoutSelection = new QVBoxLayout(pageSelection);
        verticalLayoutSelection->setSpacing(10);
        verticalLayoutSelection->setObjectName("verticalLayoutSelection");
        verticalLayoutSelection->setContentsMargins(10, 10, 10, 10);
        labelSelectTitle = new QLabel(pageSelection);
        labelSelectTitle->setObjectName("labelSelectTitle");
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        labelSelectTitle->setFont(font1);
        labelSelectTitle->setAlignment(Qt::AlignCenter);

        verticalLayoutSelection->addWidget(labelSelectTitle);

        btnRandom = new QPushButton(pageSelection);
        btnRandom->setObjectName("btnRandom");
        btnRandom->setMinimumSize(QSize(0, 40));

        verticalLayoutSelection->addWidget(btnRandom);

        listProblems = new QListWidget(pageSelection);
        listProblems->setObjectName("listProblems");

        verticalLayoutSelection->addWidget(listProblems);

        stackedWidgetProblem->addWidget(pageSelection);
        pageProblem = new QWidget();
        pageProblem->setObjectName("pageProblem");
        verticalLayoutProblem = new QVBoxLayout(pageProblem);
        verticalLayoutProblem->setSpacing(10);
        verticalLayoutProblem->setObjectName("verticalLayoutProblem");
        verticalLayoutProblem->setContentsMargins(10, 10, 10, 10);
        labelTitle = new QLabel(pageProblem);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setFont(font1);

        verticalLayoutProblem->addWidget(labelTitle);

        textProblemDescription = new QTextBrowser(pageProblem);
        textProblemDescription->setObjectName("textProblemDescription");
        textProblemDescription->setFrameShape(QFrame::NoFrame);

        verticalLayoutProblem->addWidget(textProblemDescription);

        lineProblem = new QFrame(pageProblem);
        lineProblem->setObjectName("lineProblem");
        lineProblem->setFrameShape(QFrame::Shape::HLine);
        lineProblem->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayoutProblem->addWidget(lineProblem);

        radioAns1 = new QRadioButton(pageProblem);
        radioAns1->setObjectName("radioAns1");

        verticalLayoutProblem->addWidget(radioAns1);

        radioAns2 = new QRadioButton(pageProblem);
        radioAns2->setObjectName("radioAns2");

        verticalLayoutProblem->addWidget(radioAns2);

        radioAns3 = new QRadioButton(pageProblem);
        radioAns3->setObjectName("radioAns3");

        verticalLayoutProblem->addWidget(radioAns3);

        radioAns4 = new QRadioButton(pageProblem);
        radioAns4->setObjectName("radioAns4");

        verticalLayoutProblem->addWidget(radioAns4);

        verticalSpacerProblem = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutProblem->addItem(verticalSpacerProblem);

        btnCheck = new QPushButton(pageProblem);
        btnCheck->setObjectName("btnCheck");
        btnCheck->setMinimumSize(QSize(0, 35));

        verticalLayoutProblem->addWidget(btnCheck);

        btnClose = new QPushButton(pageProblem);
        btnClose->setObjectName("btnClose");
        btnClose->setMinimumSize(QSize(0, 30));

        verticalLayoutProblem->addWidget(btnClose);

        stackedWidgetProblem->addWidget(pageProblem);

        verticalLayoutRight->addWidget(stackedWidgetProblem);

        layoutLogout = new QHBoxLayout();
        layoutLogout->setObjectName("layoutLogout");
        layoutLogout->setContentsMargins(10, -1, 10, -1);
        btnLogout = new QPushButton(frameRightPanel);
        btnLogout->setObjectName("btnLogout");
        btnLogout->setMinimumSize(QSize(0, 35));

        layoutLogout->addWidget(btnLogout);


        verticalLayoutRight->addLayout(layoutLogout);


        horizontalLayoutGame->addWidget(frameRightPanel);


        verticalLayoutMain->addLayout(horizontalLayoutGame);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidgetProblem->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Resoluci\303\263n de Problema", nullptr));
        labelAppName->setText(QCoreApplication::translate("MainWindow", "Navegaci\303\263n N\303\241utica", nullptr));
        btnAvatar->setText(QString());
#if QT_CONFIG(tooltip)
        btnPunto->setToolTip(QCoreApplication::translate("MainWindow", "Punto", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnDrawLine->setToolTip(QCoreApplication::translate("MainWindow", "L\303\255nea", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnDrawArc->setToolTip(QCoreApplication::translate("MainWindow", "Comp\303\241s", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnAnnotateText->setToolTip(QCoreApplication::translate("MainWindow", "Texto", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnProtractor->setToolTip(QCoreApplication::translate("MainWindow", "Transportador", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnRulerDistance->setToolTip(QCoreApplication::translate("MainWindow", "Regla", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnChangeColor->setToolTip(QCoreApplication::translate("MainWindow", "Cambiar Color", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnEraser->setToolTip(QCoreApplication::translate("MainWindow", "Borrador", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnClearMap->setToolTip(QCoreApplication::translate("MainWindow", "Limpiar Todo", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnShowCoordinates->setToolTip(QCoreApplication::translate("MainWindow", "Ver Coordenadas", nullptr));
#endif // QT_CONFIG(tooltip)
        labelSelectTitle->setText(QCoreApplication::translate("MainWindow", "Selecciona un Problema", nullptr));
        btnRandom->setText(QCoreApplication::translate("MainWindow", "\302\241Problema Aleatorio!", nullptr));
        labelTitle->setText(QCoreApplication::translate("MainWindow", "Problema:", nullptr));
        textProblemDescription->setStyleSheet(QCoreApplication::translate("MainWindow", "background: transparent;", nullptr));
        radioAns1->setText(QCoreApplication::translate("MainWindow", "Opci\303\263n A", nullptr));
        radioAns2->setText(QCoreApplication::translate("MainWindow", "Opci\303\263n B", nullptr));
        radioAns3->setText(QCoreApplication::translate("MainWindow", "Opci\303\263n C", nullptr));
        radioAns4->setText(QCoreApplication::translate("MainWindow", "Opci\303\263n D", nullptr));
        btnCheck->setText(QCoreApplication::translate("MainWindow", "Comprobar Respuesta", nullptr));
        btnClose->setText(QCoreApplication::translate("MainWindow", "Volver a la lista", nullptr));
        btnLogout->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #d9534f; color: white; border-radius: 4px;", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "Cerrar Sesi\303\263n", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

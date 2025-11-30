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
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
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
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *layoutMap;
    QHBoxLayout *layoutZoom;
    QLabel *lblZoomIcon;
    QPushButton *btnZoomIn;
    QPushButton *btnZoomOut;
    QSpacerItem *horizontalSpacer;
    QGraphicsView *graphicsView;
    QFrame *frameProblem;
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QLabel *labelProblemText;
    QFrame *line;
    QRadioButton *radioAns1;
    QRadioButton *radioAns2;
    QRadioButton *radioAns3;
    QRadioButton *radioAns4;
    QSpacerItem *verticalSpacer;
    QPushButton *btnCheck;
    QPushButton *btnClose;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1024, 768);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        layoutMap = new QVBoxLayout();
        layoutMap->setObjectName("layoutMap");
        layoutZoom = new QHBoxLayout();
        layoutZoom->setObjectName("layoutZoom");
        lblZoomIcon = new QLabel(centralwidget);
        lblZoomIcon->setObjectName("lblZoomIcon");
        lblZoomIcon->setMaximumSize(QSize(30, 30));
        lblZoomIcon->setPixmap(QPixmap(QString::fromUtf8(":/lupa.jpg")));
        lblZoomIcon->setScaledContents(true);

        layoutZoom->addWidget(lblZoomIcon);

        btnZoomIn = new QPushButton(centralwidget);
        btnZoomIn->setObjectName("btnZoomIn");

        layoutZoom->addWidget(btnZoomIn);

        btnZoomOut = new QPushButton(centralwidget);
        btnZoomOut->setObjectName("btnZoomOut");

        layoutZoom->addWidget(btnZoomOut);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutZoom->addItem(horizontalSpacer);


        layoutMap->addLayout(layoutZoom);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);

        layoutMap->addWidget(graphicsView);


        horizontalLayout->addLayout(layoutMap);

        frameProblem = new QFrame(centralwidget);
        frameProblem->setObjectName("frameProblem");
        frameProblem->setMinimumSize(QSize(300, 0));
        frameProblem->setMaximumSize(QSize(300, 16777215));
        frameProblem->setFrameShape(QFrame::Shape::StyledPanel);
        frameProblem->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(frameProblem);
        verticalLayout->setObjectName("verticalLayout");
        labelTitle = new QLabel(frameProblem);
        labelTitle->setObjectName("labelTitle");
        QFont font;
        font.setBold(true);
        labelTitle->setFont(font);

        verticalLayout->addWidget(labelTitle);

        labelProblemText = new QLabel(frameProblem);
        labelProblemText->setObjectName("labelProblemText");
        labelProblemText->setWordWrap(true);

        verticalLayout->addWidget(labelProblemText);

        line = new QFrame(frameProblem);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        radioAns1 = new QRadioButton(frameProblem);
        radioAns1->setObjectName("radioAns1");

        verticalLayout->addWidget(radioAns1);

        radioAns2 = new QRadioButton(frameProblem);
        radioAns2->setObjectName("radioAns2");

        verticalLayout->addWidget(radioAns2);

        radioAns3 = new QRadioButton(frameProblem);
        radioAns3->setObjectName("radioAns3");

        verticalLayout->addWidget(radioAns3);

        radioAns4 = new QRadioButton(frameProblem);
        radioAns4->setObjectName("radioAns4");

        verticalLayout->addWidget(radioAns4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btnCheck = new QPushButton(frameProblem);
        btnCheck->setObjectName("btnCheck");

        verticalLayout->addWidget(btnCheck);

        btnClose = new QPushButton(frameProblem);
        btnClose->setObjectName("btnClose");

        verticalLayout->addWidget(btnClose);


        horizontalLayout->addWidget(frameProblem);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 17));
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
        btnClose->setText(QCoreApplication::translate("MainWindow", "Volver", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

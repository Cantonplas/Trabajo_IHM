/********************************************************************************
** Form generated from reading UI file 'selectionwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTIONWINDOW_H
#define UI_SELECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectionWindow
{
public:
    QWidget *selectionOverlay;
    QPushButton *btnLogout_2;
    QPushButton *btnRandom_2;
    QPushButton *btnAvatar_2;
    QPushButton *btnToggleList_2;
    QListWidget *listProblems_2;
    QWidget *gameContentContainer;
    QPushButton *btnRandom;
    QPushButton *btnToggleList;
    QListWidget *listProblems;
    QPushButton *btnLogout;
    QPushButton *btnAvatar;

    void setupUi(QDialog *SelectionWindow)
    {
        if (SelectionWindow->objectName().isEmpty())
            SelectionWindow->setObjectName("SelectionWindow");
        SelectionWindow->resize(670, 469);
        selectionOverlay = new QWidget(SelectionWindow);
        selectionOverlay->setObjectName("selectionOverlay");
        selectionOverlay->setGeometry(QRect(470, 210, 251, 181));
        btnLogout_2 = new QPushButton(selectionOverlay);
        btnLogout_2->setObjectName("btnLogout_2");
        btnLogout_2->setGeometry(QRect(549, 437, 111, 31));
        btnRandom_2 = new QPushButton(selectionOverlay);
        btnRandom_2->setObjectName("btnRandom_2");
        btnRandom_2->setGeometry(QRect(60, 50, 231, 41));
        btnAvatar_2 = new QPushButton(selectionOverlay);
        btnAvatar_2->setObjectName("btnAvatar_2");
        btnAvatar_2->setGeometry(QRect(590, 30, 50, 50));
        btnAvatar_2->setIconSize(QSize(40, 40));
        btnToggleList_2 = new QPushButton(selectionOverlay);
        btnToggleList_2->setObjectName("btnToggleList_2");
        btnToggleList_2->setGeometry(QRect(60, 100, 231, 41));
        btnToggleList_2->setCheckable(true);
        listProblems_2 = new QListWidget(selectionOverlay);
        listProblems_2->setObjectName("listProblems_2");
        listProblems_2->setEnabled(true);
        listProblems_2->setGeometry(QRect(60, 140, 461, 311));
        gameContentContainer = new QWidget(SelectionWindow);
        gameContentContainer->setObjectName("gameContentContainer");
        gameContentContainer->setGeometry(QRect(20, 0, 561, 541));
        btnRandom = new QPushButton(gameContentContainer);
        btnRandom->setObjectName("btnRandom");
        btnRandom->setGeometry(QRect(20, 40, 231, 41));
        btnToggleList = new QPushButton(gameContentContainer);
        btnToggleList->setObjectName("btnToggleList");
        btnToggleList->setGeometry(QRect(20, 100, 231, 41));
        btnToggleList->setCheckable(true);
        listProblems = new QListWidget(gameContentContainer);
        listProblems->setObjectName("listProblems");
        listProblems->setEnabled(true);
        listProblems->setGeometry(QRect(10, 140, 461, 311));
        btnLogout = new QPushButton(gameContentContainer);
        btnLogout->setObjectName("btnLogout");
        btnLogout->setGeometry(QRect(390, 60, 111, 31));
        btnAvatar = new QPushButton(gameContentContainer);
        btnAvatar->setObjectName("btnAvatar");
        btnAvatar->setGeometry(QRect(460, 0, 50, 50));
        btnAvatar->setIconSize(QSize(40, 40));

        retranslateUi(SelectionWindow);

        QMetaObject::connectSlotsByName(SelectionWindow);
    } // setupUi

    void retranslateUi(QDialog *SelectionWindow)
    {
        SelectionWindow->setWindowTitle(QCoreApplication::translate("SelectionWindow", "Dialog", nullptr));
        btnLogout_2->setText(QCoreApplication::translate("SelectionWindow", "Cerrar sesi\303\263n", nullptr));
        btnRandom_2->setText(QCoreApplication::translate("SelectionWindow", "\302\241Problema aleatorio!", nullptr));
        btnAvatar_2->setText(QCoreApplication::translate("SelectionWindow", "PushButton", nullptr));
        btnToggleList_2->setText(QCoreApplication::translate("SelectionWindow", "Ver lista de problemas \342\226\274", nullptr));
        btnRandom->setText(QCoreApplication::translate("SelectionWindow", "\302\241Problema aleatorio!", nullptr));
        btnToggleList->setText(QCoreApplication::translate("SelectionWindow", "Ver lista de problemas \342\226\274", nullptr));
        btnLogout->setText(QCoreApplication::translate("SelectionWindow", "Cerrar sesi\303\263n", nullptr));
        btnAvatar->setText(QCoreApplication::translate("SelectionWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectionWindow: public Ui_SelectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTIONWINDOW_H

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
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectionWindow
{
public:
    QPushButton *btnAvatar;
    QPushButton *btnLogout;
    QPushButton *btnRandom;
    QPushButton *btnToggleList;
    QListView *listProblems;

    void setupUi(QDialog *SelectionWindow)
    {
        if (SelectionWindow->objectName().isEmpty())
            SelectionWindow->setObjectName("SelectionWindow");
        SelectionWindow->resize(670, 469);
        btnAvatar = new QPushButton(SelectionWindow);
        btnAvatar->setObjectName("btnAvatar");
        btnAvatar->setGeometry(QRect(590, 20, 50, 50));
        btnAvatar->setIconSize(QSize(40, 40));
        btnLogout = new QPushButton(SelectionWindow);
        btnLogout->setObjectName("btnLogout");
        btnLogout->setGeometry(QRect(549, 427, 111, 31));
        btnRandom = new QPushButton(SelectionWindow);
        btnRandom->setObjectName("btnRandom");
        btnRandom->setGeometry(QRect(220, 50, 231, 41));
        btnToggleList = new QPushButton(SelectionWindow);
        btnToggleList->setObjectName("btnToggleList");
        btnToggleList->setGeometry(QRect(220, 110, 231, 41));
        btnToggleList->setCheckable(true);
        listProblems = new QListView(SelectionWindow);
        listProblems->setObjectName("listProblems");
        listProblems->setGeometry(QRect(220, 150, 231, 291));
        listProblems->setSelectionRectVisible(true);

        retranslateUi(SelectionWindow);

        QMetaObject::connectSlotsByName(SelectionWindow);
    } // setupUi

    void retranslateUi(QDialog *SelectionWindow)
    {
        SelectionWindow->setWindowTitle(QCoreApplication::translate("SelectionWindow", "Dialog", nullptr));
        btnAvatar->setText(QCoreApplication::translate("SelectionWindow", "PushButton", nullptr));
        btnLogout->setText(QCoreApplication::translate("SelectionWindow", "Cerrar sesi\303\263n", nullptr));
        btnRandom->setText(QCoreApplication::translate("SelectionWindow", "\302\241Problema aleatorio!", nullptr));
        btnToggleList->setText(QCoreApplication::translate("SelectionWindow", "Ver lista de problemas \342\226\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectionWindow: public Ui_SelectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTIONWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(400, 300);
        pushButton = new QPushButton(LoginDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(140, 170, 121, 21));
        pushButton_2 = new QPushButton(LoginDialog);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(110, 270, 71, 20));
        lineEdit = new QLineEdit(LoginDialog);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(140, 80, 121, 20));
        label = new QLabel(LoginDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 270, 111, 16));
        lineEdit_2 = new QLineEdit(LoginDialog);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(140, 130, 121, 20));
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 60, 41, 16));
        label_3 = new QLabel(LoginDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(140, 110, 61, 16));

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("LoginDialog", "Iniciar sesi\303\263n", nullptr));
        pushButton_2->setText(QCoreApplication::translate("LoginDialog", "Registrarse", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "\302\277Necesitas una cuenta?", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "Usuario:", nullptr));
        label_3->setText(QCoreApplication::translate("LoginDialog", "Contrase\303\261a:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H

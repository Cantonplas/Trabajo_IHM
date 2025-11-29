/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QPushButton *btnCancel;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *txtUser;
    QLineEdit *txtEmail;
    QLineEdit *txtPass;
    QDateEdit *dateBirth;
    QPushButton *btnSave;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName("RegisterDialog");
        RegisterDialog->resize(400, 300);
        btnCancel = new QPushButton(RegisterDialog);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setGeometry(QRect(310, 270, 80, 18));
        verticalLayoutWidget = new QWidget(RegisterDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(80, 30, 241, 241));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        txtUser = new QLineEdit(verticalLayoutWidget);
        txtUser->setObjectName("txtUser");

        verticalLayout->addWidget(txtUser);

        txtEmail = new QLineEdit(verticalLayoutWidget);
        txtEmail->setObjectName("txtEmail");

        verticalLayout->addWidget(txtEmail);

        txtPass = new QLineEdit(verticalLayoutWidget);
        txtPass->setObjectName("txtPass");
        txtPass->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(txtPass);

        dateBirth = new QDateEdit(verticalLayoutWidget);
        dateBirth->setObjectName("dateBirth");

        verticalLayout->addWidget(dateBirth);

        btnSave = new QPushButton(verticalLayoutWidget);
        btnSave->setObjectName("btnSave");

        verticalLayout->addWidget(btnSave);

        label = new QLabel(RegisterDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 170, 301, 16));
        label_2 = new QLabel(RegisterDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 120, 421, 20));
        label_3 = new QLabel(RegisterDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(80, 70, 661, 20));
        label_4 = new QLabel(RegisterDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(80, 30, 911, 20));

        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Dialog", nullptr));
        btnCancel->setText(QCoreApplication::translate("RegisterDialog", "Cancelar", nullptr));
        txtUser->setText(QString());
        txtEmail->setText(QString());
        txtPass->setText(QString());
        btnSave->setText(QCoreApplication::translate("RegisterDialog", "Registrarse", nullptr));
        label->setText(QCoreApplication::translate("RegisterDialog", "Fecha de nacimiento:", nullptr));
        label_2->setText(QCoreApplication::translate("RegisterDialog", "Contrase\303\261a:", nullptr));
        label_3->setText(QCoreApplication::translate("RegisterDialog", "Email:", nullptr));
        label_4->setText(QCoreApplication::translate("RegisterDialog", "Usuario:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H

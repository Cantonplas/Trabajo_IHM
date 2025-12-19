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
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayoutMain;
    QStackedWidget *stackedWidget;
    QWidget *pageLogin;
    QVBoxLayout *verticalLayoutLogin;
    QLabel *label;
    QLabel *lblHeader;
    QGroupBox *groupBoxLogin;
    QFormLayout *formLayoutLogin;
    QLabel *lblUser;
    QLineEdit *txtUser;
    QLabel *lblPass;
    QLineEdit *txtPass;
    QPushButton *btnLogin;
    QLabel *labelInfo1;
    QPushButton *btnGotoRegister;
    QSpacerItem *verticalSpacerLogin;
    QWidget *pageRegister;
    QVBoxLayout *verticalLayoutReg;
    QHBoxLayout *horizontalLayoutAvatar;
    QLabel *lblAvatarPreview;
    QPushButton *btnSelectAvatar;
    QGroupBox *groupBoxReg;
    QFormLayout *formLayoutReg;
    QLabel *l1;
    QLineEdit *txtRegUser;
    QLabel *lemail;
    QLineEdit *txtRegEmail;
    QLabel *l2;
    QLineEdit *txtRegPass;
    QLabel *l3;
    QLineEdit *txtRegPass2;
    QLabel *l7;
    QDateEdit *dateBirth;
    QPushButton *btnRegister;
    QPushButton *btnGotoLogin;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(420, 550);
        LoginDialog->setMinimumSize(QSize(420, 500));
        verticalLayoutMain = new QVBoxLayout(LoginDialog);
        verticalLayoutMain->setSpacing(20);
        verticalLayoutMain->setObjectName("verticalLayoutMain");
        verticalLayoutMain->setContentsMargins(30, 30, 30, 30);
        stackedWidget = new QStackedWidget(LoginDialog);
        stackedWidget->setObjectName("stackedWidget");
        pageLogin = new QWidget();
        pageLogin->setObjectName("pageLogin");
        verticalLayoutLogin = new QVBoxLayout(pageLogin);
        verticalLayoutLogin->setSpacing(15);
        verticalLayoutLogin->setObjectName("verticalLayoutLogin");
        label = new QLabel(pageLogin);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("SimSun")});
        font.setPointSize(26);
        font.setBold(false);
        label->setFont(font);
        label->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayoutLogin->addWidget(label);

        lblHeader = new QLabel(pageLogin);
        lblHeader->setObjectName("lblHeader");
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        lblHeader->setFont(font1);
        lblHeader->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayoutLogin->addWidget(lblHeader);

        groupBoxLogin = new QGroupBox(pageLogin);
        groupBoxLogin->setObjectName("groupBoxLogin");
        formLayoutLogin = new QFormLayout(groupBoxLogin);
        formLayoutLogin->setObjectName("formLayoutLogin");
        formLayoutLogin->setVerticalSpacing(15);
        lblUser = new QLabel(groupBoxLogin);
        lblUser->setObjectName("lblUser");

        formLayoutLogin->setWidget(0, QFormLayout::ItemRole::LabelRole, lblUser);

        txtUser = new QLineEdit(groupBoxLogin);
        txtUser->setObjectName("txtUser");
        txtUser->setMinimumSize(QSize(0, 30));

        formLayoutLogin->setWidget(0, QFormLayout::ItemRole::FieldRole, txtUser);

        lblPass = new QLabel(groupBoxLogin);
        lblPass->setObjectName("lblPass");

        formLayoutLogin->setWidget(1, QFormLayout::ItemRole::LabelRole, lblPass);

        txtPass = new QLineEdit(groupBoxLogin);
        txtPass->setObjectName("txtPass");
        txtPass->setMinimumSize(QSize(0, 30));
        txtPass->setEchoMode(QLineEdit::EchoMode::Password);

        formLayoutLogin->setWidget(1, QFormLayout::ItemRole::FieldRole, txtPass);


        verticalLayoutLogin->addWidget(groupBoxLogin);

        btnLogin = new QPushButton(pageLogin);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setMinimumSize(QSize(0, 40));
        QFont font2;
        font2.setBold(true);
        btnLogin->setFont(font2);

        verticalLayoutLogin->addWidget(btnLogin);

        labelInfo1 = new QLabel(pageLogin);
        labelInfo1->setObjectName("labelInfo1");
        labelInfo1->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayoutLogin->addWidget(labelInfo1);

        btnGotoRegister = new QPushButton(pageLogin);
        btnGotoRegister->setObjectName("btnGotoRegister");
        btnGotoRegister->setMinimumSize(QSize(0, 30));
        btnGotoRegister->setFlat(false);

        verticalLayoutLogin->addWidget(btnGotoRegister);

        verticalSpacerLogin = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutLogin->addItem(verticalSpacerLogin);

        stackedWidget->addWidget(pageLogin);
        pageRegister = new QWidget();
        pageRegister->setObjectName("pageRegister");
        verticalLayoutReg = new QVBoxLayout(pageRegister);
        verticalLayoutReg->setSpacing(15);
        verticalLayoutReg->setObjectName("verticalLayoutReg");
        horizontalLayoutAvatar = new QHBoxLayout();
        horizontalLayoutAvatar->setObjectName("horizontalLayoutAvatar");
        lblAvatarPreview = new QLabel(pageRegister);
        lblAvatarPreview->setObjectName("lblAvatarPreview");
        lblAvatarPreview->setMinimumSize(QSize(64, 64));
        lblAvatarPreview->setMaximumSize(QSize(64, 64));
        lblAvatarPreview->setFrameShape(QFrame::Shape::StyledPanel);
        lblAvatarPreview->setScaledContents(true);

        horizontalLayoutAvatar->addWidget(lblAvatarPreview);

        btnSelectAvatar = new QPushButton(pageRegister);
        btnSelectAvatar->setObjectName("btnSelectAvatar");
        btnSelectAvatar->setMinimumSize(QSize(0, 30));

        horizontalLayoutAvatar->addWidget(btnSelectAvatar);


        verticalLayoutReg->addLayout(horizontalLayoutAvatar);

        groupBoxReg = new QGroupBox(pageRegister);
        groupBoxReg->setObjectName("groupBoxReg");
        formLayoutReg = new QFormLayout(groupBoxReg);
        formLayoutReg->setObjectName("formLayoutReg");
        formLayoutReg->setVerticalSpacing(10);
        l1 = new QLabel(groupBoxReg);
        l1->setObjectName("l1");

        formLayoutReg->setWidget(0, QFormLayout::ItemRole::LabelRole, l1);

        txtRegUser = new QLineEdit(groupBoxReg);
        txtRegUser->setObjectName("txtRegUser");
        txtRegUser->setMinimumSize(QSize(0, 25));

        formLayoutReg->setWidget(0, QFormLayout::ItemRole::FieldRole, txtRegUser);

        lemail = new QLabel(groupBoxReg);
        lemail->setObjectName("lemail");

        formLayoutReg->setWidget(1, QFormLayout::ItemRole::LabelRole, lemail);

        txtRegEmail = new QLineEdit(groupBoxReg);
        txtRegEmail->setObjectName("txtRegEmail");
        txtRegEmail->setMinimumSize(QSize(0, 25));

        formLayoutReg->setWidget(1, QFormLayout::ItemRole::FieldRole, txtRegEmail);

        l2 = new QLabel(groupBoxReg);
        l2->setObjectName("l2");

        formLayoutReg->setWidget(2, QFormLayout::ItemRole::LabelRole, l2);

        txtRegPass = new QLineEdit(groupBoxReg);
        txtRegPass->setObjectName("txtRegPass");
        txtRegPass->setMinimumSize(QSize(0, 25));
        txtRegPass->setEchoMode(QLineEdit::EchoMode::Password);

        formLayoutReg->setWidget(2, QFormLayout::ItemRole::FieldRole, txtRegPass);

        l3 = new QLabel(groupBoxReg);
        l3->setObjectName("l3");

        formLayoutReg->setWidget(3, QFormLayout::ItemRole::LabelRole, l3);

        txtRegPass2 = new QLineEdit(groupBoxReg);
        txtRegPass2->setObjectName("txtRegPass2");
        txtRegPass2->setMinimumSize(QSize(0, 25));
        txtRegPass2->setEchoMode(QLineEdit::EchoMode::Password);

        formLayoutReg->setWidget(3, QFormLayout::ItemRole::FieldRole, txtRegPass2);

        l7 = new QLabel(groupBoxReg);
        l7->setObjectName("l7");

        formLayoutReg->setWidget(4, QFormLayout::ItemRole::LabelRole, l7);

        dateBirth = new QDateEdit(groupBoxReg);
        dateBirth->setObjectName("dateBirth");
        dateBirth->setMinimumSize(QSize(0, 25));
        dateBirth->setCalendarPopup(true);

        formLayoutReg->setWidget(4, QFormLayout::ItemRole::FieldRole, dateBirth);


        verticalLayoutReg->addWidget(groupBoxReg);

        btnRegister = new QPushButton(pageRegister);
        btnRegister->setObjectName("btnRegister");
        btnRegister->setMinimumSize(QSize(0, 40));
        btnRegister->setFont(font2);

        verticalLayoutReg->addWidget(btnRegister);

        btnGotoLogin = new QPushButton(pageRegister);
        btnGotoLogin->setObjectName("btnGotoLogin");
        btnGotoLogin->setMinimumSize(QSize(0, 30));
        btnGotoLogin->setFlat(true);

        verticalLayoutReg->addWidget(btnGotoLogin);

        stackedWidget->addWidget(pageRegister);

        verticalLayoutMain->addWidget(stackedWidget);


        retranslateUi(LoginDialog);

        stackedWidget->setCurrentIndex(0);
        btnLogin->setDefault(true);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Acceso a Navegaci\303\263n", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "    Carta N\303\241utica", nullptr));
        lblHeader->setText(QCoreApplication::translate("LoginDialog", "Iniciar Sesi\303\263n", nullptr));
        groupBoxLogin->setTitle(QCoreApplication::translate("LoginDialog", "Credenciales", nullptr));
        lblUser->setText(QCoreApplication::translate("LoginDialog", "Usuario:", nullptr));
        lblPass->setText(QCoreApplication::translate("LoginDialog", "Contrase\303\261a:", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginDialog", "Entrar", nullptr));
        labelInfo1->setText(QCoreApplication::translate("LoginDialog", "\302\277A\303\272n no tienes cuenta?", nullptr));
        btnGotoRegister->setText(QCoreApplication::translate("LoginDialog", "Reg\303\255strate aqu\303\255", nullptr));
        lblAvatarPreview->setText(QString());
        btnSelectAvatar->setText(QCoreApplication::translate("LoginDialog", "Seleccionar Foto...", nullptr));
        groupBoxReg->setTitle(QCoreApplication::translate("LoginDialog", "Datos Personales", nullptr));
        l1->setText(QCoreApplication::translate("LoginDialog", "Usuario*:", nullptr));
#if QT_CONFIG(tooltip)
        txtRegUser->setToolTip(QCoreApplication::translate("LoginDialog", "6-15 caracteres, sin espacios", nullptr));
#endif // QT_CONFIG(tooltip)
        txtRegUser->setPlaceholderText(QCoreApplication::translate("LoginDialog", "6-15 chars (letras, nums, -_)", nullptr));
        lemail->setText(QCoreApplication::translate("LoginDialog", "Email*:", nullptr));
        txtRegEmail->setPlaceholderText(QCoreApplication::translate("LoginDialog", "ejemplo@correo.com", nullptr));
        l2->setText(QCoreApplication::translate("LoginDialog", "Contrase\303\261a*:", nullptr));
#if QT_CONFIG(tooltip)
        txtRegPass->setToolTip(QCoreApplication::translate("LoginDialog", "8-20 chars, Mayus, Minus, Digito, Especial", nullptr));
#endif // QT_CONFIG(tooltip)
        l3->setText(QCoreApplication::translate("LoginDialog", "Repetir*:", nullptr));
        l7->setText(QCoreApplication::translate("LoginDialog", "F. Nacimiento:", nullptr));
        dateBirth->setDisplayFormat(QCoreApplication::translate("LoginDialog", "dd/MM/yyyy", nullptr));
        btnRegister->setText(QCoreApplication::translate("LoginDialog", "Crear Cuenta", nullptr));
        btnGotoLogin->setText(QCoreApplication::translate("LoginDialog", "Volver a Iniciar Sesi\303\263n", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H

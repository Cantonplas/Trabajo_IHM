#include "logindialog.h"
#include "registerdialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    ui->lineEdit_1->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


//Login:
void LoginDialog::on_pushButton_clicked()
{
    QString usuario = ui->lineEdit->text();
    QString password = ui->lineEdit_1->text();

    User* loggedUser = Navigation::instance().authenticate(usuario, password); //

    if (loggedUser != nullptr) {

        this->accept();
    } else {

        QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos.");
        ui->lineEdit_1->clear();
    }
}

void LoginDialog::on_pushButton_2_clicked() // Registrarse:
{
    RegisterDialog reg;


    if (reg.exec() == QDialog::Accepted) {
        //ui->lineEdit->setText()//Hacer esto
    }
}

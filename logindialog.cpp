#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // Opcional: Poner asteriscos en el campo de contraseña
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


//Login:
void LoginDialog::on_pushButton_clicked()
{
    QString usuario = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    User* loggedUser = Navigation::instance().authenticate(usuario, password); //

    if (loggedUser != nullptr) {

        this->accept();
    } else {

        QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos.");
        ui->lineEdit_2->clear();
    }
}

#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "navigation.h" // Necesario para guardar
#include <QMessageBox>

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    connect(ui->btnCancel, &QPushButton::clicked, this, &RegisterDialog::reject);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_btnSave_clicked() //Guardar
{
    QString nick = ui->txtUser->text();
    QString pass = ui->txtPass->text();
    QString email = ui->txtEmail->text();
    QDate birth = ui->dateBirth->date();
    QImage avatar; //Por hacer, vacia por ahora


    if(nick.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Error", "Faltan datos obligatorios.");
        return;
    }

    //Comprobar si ya existe
    if(Navigation::instance().findUser(nick) != nullptr) {
        QMessageBox::warning(this, "Error", "El usuario ya existe.");
        return;
    }

    User nuevoUsuario(nick, email, pass, avatar, birth);

    try {
        Navigation::instance().addUser(nuevoUsuario);
        QMessageBox::information(this, "Éxito", "Usuario registrado correctamente.");
        this->accept();
    } catch (std::exception &e) {
        QMessageBox::critical(this, "Error", "No se pudo guardar en la base de datos.");
    }
}

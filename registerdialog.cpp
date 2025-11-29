#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "navigation.h"
#include <QMessageBox>


RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    m_editMode = false;
    this->setWindowTitle("Registrar Nuevo Usuario");
}

//Modo edición:
RegisterDialog::RegisterDialog(User* userToEdit, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog),
    m_userToEdit(userToEdit)
{
    ui->setupUi(this);
    m_editMode = true;
    this->setWindowTitle("Editar Perfil");

    ui->txtUser->setText(m_userToEdit->nickName());
    ui->txtEmail->setText(m_userToEdit->email());
    ui->txtPass->setText(m_userToEdit->password());
    ui->dateBirth->setDate(m_userToEdit->birthdate());

    //Bloquea el campo de usuario
    ui->txtUser->setReadOnly(true);
    ui->txtUser->setEnabled(false);
    ui->btnSave->setText("Actualizar");
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_btnSave_clicked()
{

    QString nick = ui->txtUser->text();
    QString pass = ui->txtPass->text();
    QString email = ui->txtEmail->text();
    QDate birth = ui->dateBirth->date();

    if (nick.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Error", "Faltan datos.");
        return;
    }

    if (m_editMode) {
        m_userToEdit->setEmail(email);
        m_userToEdit->setPassword(pass);
        m_userToEdit->setBirthdate(birth);
        // El avatar lo dejamos igual por ahora

        // Guardamos en la base de datos
        Navigation::instance().updateUser(*m_userToEdit);
        QMessageBox::information(this, "Éxito", "Perfil actualizado.");
    }
    else {
        if (Navigation::instance().findUser(nick)) {
            QMessageBox::warning(this, "Error", "El usuario ya existe.");
            return;
        }
        User newUser(nick, email, pass, QImage(), birth);
        Navigation::instance().addUser(newUser);
        QMessageBox::information(this, "Éxito", "Usuario creado.");
    }

    accept();
}

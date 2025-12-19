#include "logindialog.h"
#include "ui_logindialog.h"
#include "navigation.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDate>
#include <QRegularExpression>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_loggedUser(nullptr)
{
    ui->setupUi(this);


    ui->stackedWidget->setCurrentIndex(0);
    ui->lblHeader->setText("Iniciar Sesión");

    ui->dateBirth->setDate(QDate::currentDate().addYears(-18));
    ui->dateBirth->setMaximumDate(QDate::currentDate());

    connect(ui->btnGotoRegister, &QPushButton::clicked, this, &LoginDialog::switchToRegister);
    connect(ui->btnGotoLogin, &QPushButton::clicked, this, &LoginDialog::switchToLogin);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

User* LoginDialog::getLoggedUser() const
{
    return m_loggedUser;
}


void LoginDialog::switchToRegister()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->lblHeader->setText("Crear Nueva Cuenta");

    ui->txtRegUser->clear();
    ui->txtRegPass->clear();
    ui->txtRegPass2->clear();
    ui->txtRegEmail->clear();

    m_selectedAvatar = QImage();
    loadDefaultAvatarPreview();
}

void LoginDialog::switchToLogin()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lblHeader->setText("Iniciar Sesión");
}

bool LoginDialog::validateUsername(const QString &username)
{
    static QRegularExpression regex("^[a-zA-Z0-9_-]{6,15}$");
    return regex.match(username).hasMatch();
}

bool LoginDialog::validatePassword(const QString &password)
{
    if (password.length() < 8 || password.length() > 20) return false;

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    QString specialChars = "!@#$%&*()-+=";

    for (QChar c : password) {
        if (c.isUpper()) hasUpper = true;
        else if (c.isLower()) hasLower = true;
        else if (c.isDigit()) hasDigit = true;
        else if (specialChars.contains(c)) hasSpecial = true;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

bool LoginDialog::validateEmail(const QString &email)
{
    static QRegularExpression regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex.match(email).hasMatch();
}

bool LoginDialog::validateAge(const QDate &birthDate)
{
    QDate today = QDate::currentDate();
    QDate sixteenYearsAgo = today.addYears(-16);
    return birthDate <= sixteenYearsAgo;
}


void LoginDialog::loadDefaultAvatarPreview()
{
    QPixmap defaultPix(":/resources/user_default.png");
    if(defaultPix.isNull()) defaultPix = QPixmap(64,64);
    ui->lblAvatarPreview->setPixmap(defaultPix);
}

void LoginDialog::on_btnSelectAvatar_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Seleccionar Foto", "", "Imágenes (*.png *.jpg)");
    if (!fileName.isEmpty()) {
        QImage newImage(fileName);
        if (!newImage.isNull()) {
            m_selectedAvatar = newImage.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->lblAvatarPreview->setPixmap(QPixmap::fromImage(m_selectedAvatar));
        }
    }
}

void LoginDialog::on_btnRegister_clicked()
{
    QString user = ui->txtRegUser->text();
    QString email = ui->txtRegEmail->text();
    QString pass1 = ui->txtRegPass->text();
    QString pass2 = ui->txtRegPass2->text();
    QDate birth = ui->dateBirth->date();


    if(user.isEmpty() || email.isEmpty() || pass1.isEmpty()) {
        QMessageBox::warning(this, "Aviso", "Todos los campos son obligatorios.");
        return;
    }

    if(pass1 != pass2) {
        QMessageBox::warning(this, "Error", "Las contraseñas no coinciden.");
        return;
    }

    if(!validateUsername(user)) {
        QMessageBox::warning(this, "Usuario Inválido",
                             "El usuario debe tener entre 6 y 15 caracteres.\nSolo letras, números, guiones y guiones bajos.\nSin espacios.");
        return;
    }

    if(!validateEmail(email)) {
        QMessageBox::warning(this, "Email Inválido", "El formato del correo no es correcto.");
        return;
    }

    if(!validatePassword(pass1)) {
        QMessageBox::warning(this, "Contraseña Débil",
                             "La contraseña debe tener 8-20 caracteres e incluir:\n- Mayúscula\n- Minúscula\n- Dígito\n- Carácter especial (!@#$%&*()-+=)");
        return;
    }

    if(!validateAge(birth)) {
        QMessageBox::warning(this, "Edad", "Debes ser mayor de 16 años para registrarte.");
        return;
    }

    if (Navigation::instance().findUser(user) != nullptr) {
        QMessageBox::warning(this, "Error", "El nombre de usuario ya está en uso. Elige otro.");
        return;
    }

    QImage finalAvatar = m_selectedAvatar;
    if(finalAvatar.isNull()) {
        finalAvatar.load(":/resources/user_default.png");
    }

    User newUser(user, email, pass1, finalAvatar, birth);

    Navigation::instance().addUser(newUser);
    QMessageBox::information(this, "Exito", "Se ha registrado el usuario correctamente");
    ui->stackedWidget->setCurrentIndex(0);

}


void LoginDialog::on_btnLogin_clicked()
{
    QString user = ui->txtUser->text();
    QString pass = ui->txtPass->text();

    m_loggedUser = Navigation::instance().authenticate(user, pass);

    if (m_loggedUser) {
        accept();
    } else {
        QMessageBox::critical(this, "Error", "Usuario o contraseña incorrectos.");
    }
}

#pragma once

#include <QDialog>
#include <QImage>
#include "navtypes.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    User* getLoggedUser() const;

private slots:
    void on_btnLogin_clicked();
    void switchToRegister();
    void switchToLogin();
    void on_btnSelectAvatar_clicked();
    void on_btnRegister_clicked();

private:
    Ui::LoginDialog *ui;
    User* m_loggedUser;
    QImage m_selectedAvatar;

    void loadDefaultAvatarPreview();

    bool validateUsername(const QString &username);
    bool validatePassword(const QString &password);
    bool validateEmail(const QString &email);
    bool validateAge(const QDate &birthDate);
};

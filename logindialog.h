#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "navigation.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    // Login:
    void on_pushButton_clicked();
    //Registrarse:
    void on_pushButton_2_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H

#pragma once
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

    User* getLoggedUser() const { return m_loggedUser; }

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::LoginDialog *ui;
    User* m_loggedUser = nullptr;
};

#endif // LOGINDIALOG_H

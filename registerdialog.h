#pragma once
#include <QDialog>
#include "navtypes.h"

namespace Ui { class RegisterDialog; }

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:

    explicit RegisterDialog(QWidget *parent = nullptr);


    explicit RegisterDialog(User* userToEdit, QWidget *parent = nullptr);

    ~RegisterDialog();

private slots:
    void on_btnSave_clicked();

private:
    Ui::RegisterDialog *ui;
    User *m_userToEdit = nullptr;
    bool m_editMode = false;
};

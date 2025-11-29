#pragma once
#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H

#include <QDialog>
#include <QListWidgetItem>
#include <QListWidget>
#include "navtypes.h"

namespace Ui {
class SelectionWindow;
}

class SelectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SelectionWindow(User *user, QDialog *parent = nullptr);
    ~SelectionWindow();

private slots:
    void on_btnRandom_clicked();
    void on_btnToggleList_toggled(bool checked);
    void on_btnLogout_clicked();
    void on_listProblems_itemClicked(QListWidgetItem *item);
    void on_editProfile_triggered();

private:
    Ui::SelectionWindow *ui;
    User *m_currentUser;

    void loadUserData();
    void loadProblems();
    void setupAvatarMenu();

    // Método auxiliar nuevo
    void openProblem(const Problem &p);
};

#endif // SELECTIONWINDOW_H

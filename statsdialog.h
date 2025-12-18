#pragma once

#include <QDialog>
#include "navtypes.h"

namespace Ui {
class StatsDialog;
}

class StatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatsDialog(User* user, QWidget *parent = nullptr);
    ~StatsDialog();

private slots:
    void on_btnFilter_clicked();

private:
    Ui::StatsDialog *ui;
    User* m_user;

    void loadStats();
};


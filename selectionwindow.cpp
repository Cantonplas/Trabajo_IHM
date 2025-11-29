#include "selectionwindow.h"
#include "ui_selectionwindow.h"
#include "navigation.h"
#include "mainwindow.h"
#include "registerdialog.h"
#include "mainwindow.h"
#include <QMenu>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QEventLoop>

SelectionWindow::SelectionWindow(User *user, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::SelectionWindow),
    m_currentUser(user)
{
    ui->setupUi(this);

    loadUserData();
    loadProblems();
    setupAvatarMenu();
}

SelectionWindow::~SelectionWindow()
{
    delete ui;
}


void SelectionWindow::loadUserData()
{
    if(m_currentUser){
    QPixmap pixmap = QPixmap::fromImage(m_currentUser->avatar());
    if (pixmap.isNull()) {
        // Si no tiene avatar,cargar uno por defecto
    } else {
        ui->btnAvatar->setIcon(QIcon(pixmap));
    }
    }
}

void SelectionWindow::setupAvatarMenu()
{
    QMenu *menu = new QMenu(this);

    QAction *editAction = menu->addAction("Editar Perfil");
    connect(editAction, &QAction::triggered, this, &SelectionWindow::on_editProfile_triggered);

    ui->btnAvatar->setMenu(menu);

}

void SelectionWindow::loadProblems()
{
    ui->listProblems->clear();
    const auto &problems = Navigation::instance().problems();

    for (int i = 0; i < problems.size(); ++i) {
        QListWidgetItem *item = new QListWidgetItem(problems[i].text());
        item->setData(Qt::UserRole, i);
        ui->listProblems->addItem(item);
    }
}


void SelectionWindow::on_btnToggleList_toggled(bool checked)
{
    ui->listProblems->setVisible(checked);
    ui->btnToggleList->setText(checked ? "Ocultar lista ▲" : "Ver lista de problemas ▼");
}


void SelectionWindow::on_listProblems_itemClicked(QListWidgetItem *item)
{
    MainWindow *w = new MainWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();

    this->hide();

    QEventLoop loop;
    connect(w, &QWidget::destroyed, &loop, &QEventLoop::quit);
    loop.exec();

    this->show();

}
void SelectionWindow::on_btnRandom_clicked()
{
    const auto &problems = Navigation::instance().problems();
    if (problems.isEmpty()) return;

    MainWindow *w = new MainWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();

    this->hide();

    QEventLoop loop;
    connect(w, &QWidget::destroyed, &loop, &QEventLoop::quit);
    loop.exec();

    this->show();
}

void SelectionWindow::on_editProfile_triggered()
{
    RegisterDialog dialog(m_currentUser, this);
    if (dialog.exec() == QDialog::Accepted) {
        loadUserData();
    }
}

void SelectionWindow::on_btnLogout_clicked()
{
    this->reject();
}

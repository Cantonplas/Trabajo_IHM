#include "selectionwindow.h"
#include "ui_selectionwindow.h"
#include "navigation.h"
#include "mainwindow.h"
#include "registerdialog.h"
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
        if (!pixmap.isNull()) {
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

    int index = item->data(Qt::UserRole).toInt();
    const auto &problems = Navigation::instance().problems();

    if (index >= 0 && index < problems.size()) {
        const Problem &selectedProblem = problems[index];


        MainWindow *w = new MainWindow(selectedProblem, nullptr);
        w->setAttribute(Qt::WA_DeleteOnClose);

        this->hide();


        QEventLoop loop;
        connect(w, &QWidget::destroyed, &loop, &QEventLoop::quit);
        w->show();
        loop.exec();

        this->show();
    }
}

void SelectionWindow::on_btnRandom_clicked()
{
    const auto &problems = Navigation::instance().problems();
    if (problems.isEmpty()) {
        QMessageBox::warning(this, "Error", "No hay problemas en la base de datos.");
        return;
    }

    int randomIndex = QRandomGenerator::global()->bounded(problems.size());
    const Problem &randomProblem = problems[randomIndex];

    MainWindow *w = new MainWindow(randomProblem, nullptr);
    w->setAttribute(Qt::WA_DeleteOnClose);

    this->hide();

    QEventLoop loop;
    connect(w, &QWidget::destroyed, &loop, &QEventLoop::quit);
    w->show();
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
    not_logged = true;
    this->reject();
}

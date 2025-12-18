#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

const int RESTART_CODE = 1000;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int currentExitCode = 0;

    do {
        LoginDialog login;
        if (login.exec() != QDialog::Accepted) {
            break;
        }

        MainWindow w(login.getLoggedUser());
        w.show();

        currentExitCode = a.exec();

    } while (currentExitCode == RESTART_CODE);

    return currentExitCode;
}

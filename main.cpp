#include "mainwindow.h"
#include "logindialog.h"
#include "selectionwindow.h"
#include "navigation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    while (true) {
        LoginDialog login;
        if (login.exec() != QDialog::Accepted) {
            break;
        }

        User* currentUser = login.getLoggedUser();

        SelectionWindow selection(currentUser);
        selection.exec();
    }

    return 0;
}

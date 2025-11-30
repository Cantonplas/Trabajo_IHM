#include "mainwindow.h"
#include "logindialog.h"
#include "selectionwindow.h"
#include "navigation.h"
#include <QApplication>

bool not_logged{true};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    User* currentUser;

    while (true) {
        if(not_logged){
        LoginDialog login;
        if (login.exec() != QDialog::Accepted) {
            break;
        }

        currentUser = login.getLoggedUser();
        not_logged = false;
        }else{
        SelectionWindow selection(currentUser);
        selection.exec();
        }
    }

    return 0;
}

#include "mainwindow.h"
#include "logindialog.h"
#include "selectionwindow.h"
#include "navigation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    while (true) {
        //Mostrar Login
        LoginDialog login;
        if (login.exec() != QDialog::Accepted) {
            break;
        }
        User* currentUser = login.getLoggedUser();

        SelectionWindow selection(currentUser);
        selection.show();

        QEventLoop loop;
        QObject::connect(&selection, &QWidget::destroyed, &loop, &QEventLoop::quit);
    }

    return 0;
}

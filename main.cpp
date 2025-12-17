#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1. Mostrar Login
    LoginDialog login;
    if (login.exec() != QDialog::Accepted) {
        return 0; // Si cierra el login, sale de la app
    }

    // 2. Obtener usuario logueado
    User* currentUser = login.getLoggedUser();

    // 3. Arrancar MainWindow directamente pasándole el usuario
    // MainWindow se encargará de mostrar el overlay de selección al inicio.
    MainWindow w(currentUser);
    w.show();

    return a.exec();
}

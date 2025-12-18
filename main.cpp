#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

const int RESTART_CODE = 1000;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int currentExitCode = 0;

    do {
        // 1. Mostrar Login
        LoginDialog login;
        if (login.exec() != QDialog::Accepted) {
            // Si el usuario da a Cancelar o cierra la ventana de login, salimos de la app
            break;
        }

        // 2. Si el login es correcto, creamos y mostramos la MainWindow
        // Nota: MainWindow debe destruirse al acabar esta iteración para liberar memoria
        MainWindow w(login.getLoggedUser());
        w.show();

        // 3. Arrancamos el bucle de eventos y esperamos a que w se cierre
        currentExitCode = a.exec();

        // 4. Si el código de salida es RESTART_CODE, repetimos el bucle (volvemos al Login)
    } while (currentExitCode == RESTART_CODE);

    return currentExitCode;
}

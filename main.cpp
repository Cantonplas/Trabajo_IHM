#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

const int RESTART_CODE = 1000;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/style.qss");
    if(file.open(QFile::ReadOnly | QFile::Text)) {
        // 2. Leer el contenido
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();

        // 3. Aplicar el estilo a toda la aplicación
        a.setStyleSheet(styleSheet);
        file.close();
    }

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

#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include<QDir>
#include "navigation.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog login;
    if(login.exec()== QDialog::Accepted){
        MainWindow w;
        w.show();
        qDebug() << "Working directory:" << QDir::currentPath();
    }
    //qDebug() << "DB path:" << Navigation::DEFAULT_DB_PATH();
    return a.exec();
}

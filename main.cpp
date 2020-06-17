#include "mainwindow.h"
#include <QApplication>
#include "conexion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    conexion  mybas;
    mybas.connection();
    return a.exec();
}

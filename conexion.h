#ifndef CONEXION_H
#define CONEXION_H
#include<QSqlDatabase>
#include "mainwindow.h"



class conexion
{
public:
    conexion();
    ~conexion();

    static bool connection();
     void closeconnecxion();




private:
    Ui::MainWindow *ui;
     //QSqlDatabase db;
};

#endif // CONEXION_H


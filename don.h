#ifndef DON_H
#define DON_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSystemTrayIcon>
#include <QDate>
class don
{

    QString nom_e;
    QString num_e;
    QString tel_e;
    QString email_e;
    QDate date_e;
    QString montant_e;
    QString cin_e;
    QString adress_e;
public:
    don();
    don(QString,QString,QString,QString,QDate,QString,QString,QString);
    void ajouterdon();
    void supprimerdon();
    bool rechercherdon(QString);
    void modifierdon();
    QSqlQueryModel *rechercher(QString);
    QSqlQueryModel* tri();
    QSqlQueryModel*  countdon1(QString n);
    QSqlQueryModel*  countdon2();
    QSqlQueryModel*  countdon3();
    static QSqlQueryModel *afficher_nom(QString name);
    void notification_e(QString );
};


#endif // DON_H

#ifndef DONNEUR_H
#define DONNEUR_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSystemTrayIcon>
#include <QDate>

class donneur
{


        QString civilite;
        QString nom;
        QString prenom;
        QString proffession;
        QString cin;
        QString adresse;
        QDate datenassaissance;
        QString email;
        QString tel;
        QString region;


    public:
        donneur();
         donneur(QString,QString ,QString,QString,QString,QString,QDate,QString,QString,QString);
         void ajouterdonneur();
         void supprimerdonneur();
         bool recherchedonneur(QString);
         void modifier();
         QSqlQueryModel *rechercher(QString);
         QSqlQueryModel *rechercher_nom(QString);
         QSqlQueryModel* countregion();
         static QSqlQueryModel *afficher(QString id);
         static QSqlQueryModel *afficher_nom(QString name);

          void notification(QString );




         QString Getcivilite()
         {
             return this->civilite;
         }
         QString Getnom()
         {
             return this->nom;
         }
         QString Getprenom()
         {
             return this->prenom;
         }
         QString Getproffession()
         {
             return this->proffession;
         }
         QString Getcin()
         {
             return this->cin;
         }
         QString Getadresse()
         {
             return this->adresse;
         }

    };



#endif // DONNEUR_H

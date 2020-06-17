#include "don.h"
#include <QString>
#include<QVariant>
#include<QDebug>
#include<QSqlDatabase>
#include <iostream>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDate>
#include <qvariant.h>

don::don()
{

}


don::don(QString nom_e,QString num_e,QString tel_e,QString email_e,QDate date_e,QString montant_e,QString cin_e,QString adress_e)
{


    this-> nom_e=nom_e;
    this->num_e=num_e;
    this-> tel_e=tel_e;
    this->email_e=email_e;
    this->date_e=date_e;
    this->montant_e=montant_e;
    this->cin_e=cin_e;
    this->adress_e=adress_e;



}




 void don::ajouterdon()

{

    QSqlQuery query;

   query.prepare("INSERT INTO DONS (nom_e,num_e,tel_e,email_e,date_e,montant_e,cin_e,adress_e)" "VALUES ( :NOM_E,:NUM_E,:TEL_E,:EMAIL_E,:DATE_E,:MONTANT_E,:CIN_E,:ADRESS_E)");
  query.bindValue(":NOM_E",nom_e);
  query.bindValue(":NUM_E",num_e);
  query.bindValue(":TEL_E",tel_e);
  query.bindValue(":EMAIL_E",email_e);
  query.bindValue(":DATE_E",date_e);
  query.bindValue(":MONTANT_E",montant_e);
  query.bindValue(":CIN_E",cin_e);
  query.bindValue(":ADRESS_E",adress_e);

   if(query.exec()){qDebug()<<"saved\n";}

      else{qDebug()<<"not saved!!!\n";}




}



 void don::supprimerdon()
 {


     QSqlQuery query ;
        query.prepare("DELETE from DONS where NUM_E = '"+num_e+"'");
     if(query.exec())
        {

        qDebug()<<" supprimer!! \n";
    }
                      else{ qDebug()<<" echec de la suppression!! \n";}



 }




 void don::modifierdon()
 {

     QSqlQuery query ;
        query.prepare("update DONS set  nom_e=:NOM_E, num_e=:NUM_E, tel_e=:TEL_E,email_e=:EMAIL_E,date_e=:DATE_E,montant_e=:MONTANT_E,cin_e=:CIN_E ,adress_e=:ADRESS_E where(num_e=:NUM_E)");
        query.bindValue(":NOM_E",nom_e);
        query.bindValue(":NUM_E",num_e);
        query.bindValue(":TEL_E",tel_e);
        query.bindValue(":EMAIL_E",email_e);
        query.bindValue(":DATE_E",date_e);
        query.bindValue(":MONTANT_E",montant_e);
        query.bindValue(":CIN_E",cin_e);
        query.bindValue(":ADRESS_E",adress_e);

        if(query.exec())
       {


        qDebug()<<" mis a jour effectuuer!!\n";
    }

     else{ qDebug()<<" echec de la mis a jour!!\n";}


 }


 QSqlQueryModel * don ::rechercher(QString id)
 {


     QSqlQueryModel *mqy=new::QSqlQueryModel;
                mqy->setQuery("select NOM_E,NUM_E,CIN_E,MONTANT_E from DONS where NUM_E like '%"+id+"%'");
                return mqy;


 }



 QSqlQueryModel * don::afficher_nom(QString name)
 {
     QSqlQueryModel *mqy=new::QSqlQueryModel;
                mqy->setQuery("select *from DONS where NOM_E like '%"+name+"%'");
                return mqy;


 }


 void  don::notification_e(QString num_e)

 {

     QSystemTrayIcon *notif= new  QSystemTrayIcon;
     notif->show();
    // notif->setIcon(QIcon());
     notif->showMessage("service don","un nouveau don de types DONS a ete ajouter NUMERO ref: "+num_e+"",QSystemTrayIcon::Information,1000);

 }

 QSqlQueryModel* don ::tri()
 {

     QSqlQuery* qry = new QSqlQuery();
      QSqlQueryModel* modal=new QSqlQueryModel();
     qry->prepare("select *from DONS order by DATE_E");
     qry->exec();
     modal->setQuery(*qry);

   return modal;

 }



 QSqlQueryModel* don ::countdon1(QString n)
 {

     QSqlQuery* qry = new QSqlQuery();
      QSqlQueryModel* modal=new QSqlQueryModel();
      qry->prepare("select *from DONS where extract(DAY from DATE_E )="+n+" ");


      qry->exec();
     modal->setQuery(*qry);

   return modal;

 }





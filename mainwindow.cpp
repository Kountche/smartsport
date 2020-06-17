#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "conexion.h"
#include "don.h"
#include<QMessageBox>
#include<QDesktopServices>
#include<QDebug>
#include<QUrl>
#include<string>
#include<QFileDialog>
#include<QDateEdit>
#include<QDate>
#include "smtp.h"
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include "donneur.h"
#include <QSqlRecord>
#include <QMovie>
#include <QIcon>
#include<QMessageBox>
#include<QDesktopServices>
#include<QDebug>
#include <QtWidgets>
#include <QBarSet>
#include <QLabel>
#include<QUrl>
#include<string>
#include<QFileDialog>
#include <QPixmap>
#include<QDateEdit>
#include<QDate>
#include <QTcpSocket>
#include <QTranslator>
#include <QtCharts>
#include <QLineSeries>
#include <statistique.h>

using namespace QtCharts;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ui->afficherstat->setIcon(ButtonIcon);
      //ui->statistique->setIcon(ButtonIcon);

    //ui->stackedWidget->setCurrentIndex(1);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void connect()
{
QTcpSocket socket;
socket.connectToHost("voidrealms.com",80);
if(socket.waitForConnected(3000))
   {
qDebug()<<"Connected!";
}
}

/*--------------------------------------------------------------------------------------------------------------------------------*/
//donneur
//ajouter
void MainWindow::on_ajouter_d_clicked()
{

        QString civilite=ui->civilite_p->currentText();
            QString nom=ui->nom_p->text();
            QString prenom=ui->prenom_p->text();
            QString proffession= ui->proffession_p->text();
            QString cin=ui->cin_p->text();
             QString adresse=ui->adresse_p->text();
             QDate datenassaissance=ui->datenaissance_p->date();
             QString email= ui->email_p->text();
             QString tel= ui->tel_p->text();
             QString region= ui->region_p->text();




             donneur cp(civilite,nom,prenom, proffession,cin,adresse,datenassaissance,email,tel,region);

             if(nom.isEmpty() || adresse.isEmpty() || email.isEmpty())
                 {
                     QMessageBox::critical(0,qApp->tr("erreur"),
                                           qApp->tr("veillez remplir les champs vides."),QMessageBox::Cancel);
                 }

             else if(nom==adresse || nom==email || adresse==email)
                {
                    QMessageBox::critical(0,qApp->tr("erreur"),
                                          qApp->tr("Des champs sont identiques."),QMessageBox::Cancel);
                }

             else{
                 cp.ajouterdonneur();
                 cp.notification(cin);
                ui->nom_p->clear();
                ui->prenom_p->clear();
                ui->civilite_p->clear();
                ui->datenaissance_p->clear();
                ui->email_p->clear();
                ui->tel_p->clear();
                ui->cin_p->clear();
                ui->region_p->clear();
                ui->proffession_p->clear();
                ui->adresse_p->clear();
                Smtp* smtp=new Smtp("amadoukountcheharouna@gmail.com"," ","smtp.gmail.com");
               connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

                    smtp->sendMail("amadoukountcheharouna@gmail.com", email , "Sportzen","Bienvenu "+nom+" "+prenom+" a notre association sportzen !");
                 QMessageBox::information(0,qApp->tr("erreur"),
                                       qApp->tr(" Le donneur a été ajouter."),QMessageBox::Yes);

                 }


    }

//// afficher
void MainWindow::on_afficher_d_clicked()
{
    QSqlQueryModel* modal=new QSqlQueryModel();
       QSqlQuery* qry = new QSqlQuery();
       qry->prepare("select *from DONNEURS ORDER by DATENASSAISSANCE DESC");
       qry->exec();
       modal->setQuery(*qry);
       ui->tableView_2->setModel(modal);

       qDebug()<<(modal->rowCount());
}


//modifier
void MainWindow::on_modifier_d_clicked()
{
    QString nom=ui->nom_p->text();
       QString prenom=ui->prenom_p->text();
        QString tel=ui->tel_p->text();
         QString adresse=ui->adresse_p->text();
            QString cin=ui->cin_p->text();
            QString email=ui->email_p->text();
            QDate datenassaissance=ui->datenaissance_p->date();
            QString proffession =ui->proffession_p->text();
            QString region =ui->region_p->text();
             QString civilite =ui->civilite_p->currentText();


 donneur cp(civilite,nom,prenom,proffession,cin,adresse,datenassaissance,email,tel,region);
 cp.modifier();
   ui->nom_p->clear();
     ui->prenom_p->clear();
       ui->adresse_p->clear();
            ui->cin_p->clear();
            ui->civilite_p->clear();
            ui->region_p->clear();
            ui->proffession_p->clear();
            ui->datenaissance_p->clear();
            ui->email_p->clear();
            ui->tel_p->clear();
}
//reafficher les valeurs
void MainWindow::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    int r=index.row();
    ui->nom_p->setText(index.sibling(r,1).data().toString());
    ui->prenom_p->setText(index.sibling(r,2).data().toString());
    ui->adresse_p->setText(index.sibling(r,5).data().toString());
    // ui->datenaissance_p->setText(index.sibling(r,6).data().toString());
     ui->tel_p->setText(index.sibling(r,8).data().toString());
    ui->email_p->setText(index.sibling(r,7).data().toString());
    ui->region_p->setText(index.sibling(r,9).data().toString());
    ui->proffession_p->setText(index.sibling(r,3).data().toString());
    ui->cin_p->setText(index.sibling(r,4).data().toString());
}
//supprimer
void MainWindow::on_supprimer_d_clicked()
{
    QString cin=ui->cin_p->text();
    QDate datenassaissance=ui->datenaissance_p->date();

    donneur cp("","","","",cin,"",datenassaissance ,"","","");
    cp.supprimerdonneur();
     ui->cin_p->clear();
     ui->nom_p->clear();
       ui->prenom_p->clear();
         ui->adresse_p->clear();
              ui->cin_p->clear();
              ui->civilite_p->clear();
              ui->region_p->clear();
              ui->proffession_p->clear();
              //ui->datenaissance_p->clear();
              ui->email_p->clear();
              ui->tel_p->clear();
}




//rechercher

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
        QString name;
        donneur cp;
        QString id=ui->recherche_d->text();
       // QString name=ui->lineEdit->text();

       ui->tableView_2->setModel(cp.rechercher(id));
        ui->tableView_2->setModel(cp.rechercher_nom(name));
       ui->tableView_2->clearSelection();



}


//ouvrir un ficher
void MainWindow::on_fichier_d_clicked()
{
    QString file=QFileDialog::getOpenFileName( this ,tr("open file"),"C://","All files(*.*);;Text file(*.txt);;Music File(*.mp3)");
    QMessageBox :: information(this,tr("File Name"),file);
}

//imprimer la liste tableview2
void MainWindow::on_imprimer_d_clicked()
{
    QPrinter printer;
    printer.setPrinterName("imprmer le nom");
    QPrintDialog dialog(&printer,this);
    if(dialog.exec()==QDialog ::Rejected) return;
    ui->tableView_2->render(&printer);
}


//rechercher ok no ,id
void MainWindow::on_rechercher_d_clicked()
{
        donneur cp;
        QString id=ui->recherche_d->text();

       ui->tableView_2->setModel(cp.afficher(id));
       ui->tableView_2->clearSelection();

       QString name=ui->recherche_d->text();
       ui->tableView_2->setModel(cp.afficher_nom(name));



}


void MainWindow::on_pdf_d_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save document...", qApp->applicationDirPath(), "*.Pdf");
            if (!fileName.isEmpty())
            {
              QPrinter printer;
              printer.setFullPage(true);
              printer.setPaperSize(QPrinter::A4);
              printer.setOrientation(QPrinter::Portrait);
              printer.setOutputFormat(QPrinter::PdfFormat);
              printer.setOutputFileName(fileName);
              ui->tableView_2-> render(&printer);
            }
}

//quitter
void MainWindow::on_quitter_d_clicked()
{
    this->hide();
}

void MainWindow::on_email_d_clicked()
{
    gemail=new email(this);
    gemail->show();
    this->hide();
}


void MainWindow::on_tri_d_clicked()
{
    don cp;

    QString id=ui->recherche_d->text();

    QSqlQueryModel* modal=cp.tri();

    ui->tableView_2->setModel(modal);

       qDebug()<<(modal->rowCount());

}

/*--------------------------------------------------------------------------------------------------------------------------------*/
//don



//ajouter
void MainWindow::on_ajouter_1_clicked()
{
    QString nom_e=ui->nom_e->text();
        QString num_e=ui->num_e->text();
        QString tel_e=ui->tel_e->text();
        QString email_e= ui->email_e->text();
        QDate date_e=ui->date_e->date();
         QString montant_e=ui->montant_e->text();
         QString cin_e= ui->cin_e->text();
         QString adress_e= ui->adress_e->text();



         don cp(nom_e,num_e,tel_e,email_e,date_e,montant_e,cin_e,adress_e);
         if(num_e.isEmpty() || cin_e.isEmpty() || email_e.isEmpty())
             {
                 QMessageBox::critical(0,qApp->tr("erreur"),
                                       qApp->tr("veillez remplir les champs vides."),QMessageBox::Cancel);
             }

         else if(num_e==cin_e || nom_e==email_e || cin_e==num_e)
            {
                QMessageBox::critical(0,qApp->tr("erreur"),
                                      qApp->tr("Des champs sont identiques."),QMessageBox::Cancel);
            }

         else{
         cp.ajouterdon();
         cp.notification_e(num_e);
         ui->cin_e->clear();
         ui->nom_e->clear();
           ui->num_e->clear();
             ui->adress_e->clear();
               ui->montant_e->clear();

                  ui->tel_e->clear();
                  ui->email_e->clear();
                  Smtp* smtp=new Smtp("amadoukountcheharouna@gmail.com"," ","smtp.gmail.com");
                 connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

                      smtp->sendMail("amadoukountcheharouna@gmail.com"," email_e" , "Sportzen","Bienvenu "+nom_e+"  a notre association sportzen !");
                   QMessageBox::information(0,qApp->tr("erreur"),
                                         qApp->tr(" Le donneur a été ajouter."),QMessageBox::Yes);
         }

}

//affiche
void MainWindow::on_afficher_1_clicked()
{
    QSqlQueryModel* modal=new QSqlQueryModel();
       QSqlQuery* qry = new QSqlQuery();
       qry->prepare("select  * from DONS ORDER by DATE_E DESC");
       qry->exec();
       modal->setQuery(*qry);
       ui->tableView_e->setModel(modal);

       qDebug()<<(modal->rowCount());
}
//supprimer
void MainWindow::on_supprimer_1_clicked()
{
    QString num_e=ui->num_e->text();
     QDate date_e=ui->date_e->date();

    don cp("",num_e,"","",date_e,"","" ,"");
    cp.supprimerdon();

     ui->cin_e->clear();
     ui->nom_e->clear();
       ui->num_e->clear();
         ui->adress_e->clear();
           ui->montant_e->clear();

              ui->tel_e->clear();

              ui->email_e->clear();

}

void MainWindow::on_tableView_e_doubleClicked(const QModelIndex &index)
{
    int r=index.row();
    ui->nom_e->setText(index.sibling(r,0).data().toString());
    ui->num_e->setText(index.sibling(r,1).data().toString());
    ui->tel_e->setText(index.sibling(r,2).data().toString());
     ui->email_e->setText(index.sibling(r,3).data().toString());
     ui->montant_e->setText(index.sibling(r,5).data().toString());
    //ui->nb_e->setText(index.sibling(r,6).data().toString());
    ui->cin_e->setText(index.sibling(r,7).data().toString());
    ui->adress_e->setText(index.sibling(r,7).data().toString());
}



//modifier
void MainWindow::on_modifier_1_clicked()
{
    QString nom_e=ui->nom_e->text();
        QString num_e=ui->num_e->text();
        QString tel_e=ui->tel_e->text();
        QString email_e= ui->email_e->text();
        QDate date_e=ui->date_e->date();
         QString montant_e=ui->montant_e->text();
         QString cin_e= ui->cin_e->text();
         QString adress_e= ui->adress_e->text();



         don cp(nom_e,num_e,tel_e,email_e,date_e,montant_e,cin_e,adress_e);
         cp.modifierdon();
         ui->cin_e->clear();
         ui->nom_e->clear();
           ui->num_e->clear();
             ui->adress_e->clear();
               ui->montant_e->clear();

                  ui->tel_e->clear();
                  ui->email_e->clear();
}


//quitter
void MainWindow::on_quitter_1_clicked()
{
    this->hide();
}


//ouvrir un ficher
void MainWindow::on_fichier_1_clicked()
{
    QString file=QFileDialog::getOpenFileName( this ,tr("open file"),"C://","All files(*.*);;Text file(*.txt);;Music File(*.mp3)");
    QMessageBox :: information(this,tr("File Name"),file);
}

//imprimer la liste tableview2
void MainWindow::on_imprimer_1_clicked()
{
    QPrinter printer;
    printer.setPrinterName("imprmer le nom");
    QPrintDialog dialog(&printer,this);
    if(dialog.exec()==QDialog ::Rejected) return;
    ui->tableView_2->render(&printer);
}



void MainWindow::on_pdf_1_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save document...", qApp->applicationDirPath(), "*.Pdf");
            if (!fileName.isEmpty())
            {
              QPrinter printer;
              printer.setFullPage(true);
              printer.setPaperSize(QPrinter::A4);
              printer.setOrientation(QPrinter::Portrait);
              printer.setOutputFormat(QPrinter::PdfFormat);
              printer.setOutputFileName(fileName);
              ui->tableView_2-> render(&printer);
            }
}



//page email
void MainWindow::on_email_1_clicked()
{
    gemail=new email(this);
    gemail->show();
    this->hide();
}


void MainWindow::on_tri_1_clicked()
{
    don cp;

    QString id=ui->recherche_1->text();

    QSqlQueryModel* modal=cp.tri();

    ui->tableView_e->setModel(modal);

       qDebug()<<(modal->rowCount());

}


//rechercher

void MainWindow::on_lineEdit_1_textChanged(const QString &arg1)
{
       // QString name;
        donneur cp;
        QString id=ui->recherche_1->text();
        QString name=ui->recherche_1->text();

       ui->tableView_e->setModel(cp.rechercher(id));
        ui->tableView_e->setModel(cp.rechercher_nom(name));
       ui->tableView_e->clearSelection();



}



//rechercher ok no ,id
void MainWindow::on_rechercher_1_clicked()
{
        donneur cp;
        QString id=ui->recherche_1->text();

       ui->tableView_e->setModel(cp.afficher(id));
       ui->tableView_e->clearSelection();

       QString name=ui->recherche_1->text();
       ui->tableView_e->setModel(cp.afficher_nom(name));



}


//visitez la page fb
void MainWindow::on_commandLinkButton_clicked()
{
    QString link="https://www.facebook.com/Mercedes-Benz-Tunisie-1094449294019699/";
    QDesktopServices::openUrl(QUrl(link));
}

//visitez le site web
void MainWindow::on_commandLinkButton_2_clicked()
{
    QString link="https://www.automobile.tn";
    QDesktopServices::openUrl(QUrl(link));
}







/*--------------------------------------------------------------------------------------------------------------------------------*/
//statistique
void MainWindow::on_afficherstat_clicked()
{
    QBarSet *set0=new QBarSet("region");

    int n1=0;

     int region[100];
     int j=0;
     for(j=0;j<100;j++)
       {
        region[j]=0;
     }
    donneur cp;
    QString name[20];

     QSqlQueryModel*  modal1=cp.countregion();
    qDebug()<<(n1=modal1->rowCount());
    for (int i = 0; i <= modal1->rowCount(); i++) {

           region[i] = modal1->record(i).value("region").toInt();
             qDebug()<<region[i];
           name[i] = modal1->record(i).value("nom").toString();
           qDebug()<<name[i];

       }

*set0<<region[0]<<region[1]<<region[2]<<region[3]<<region[4]<<region[5]<<region[6];

    QBarSeries *series=new QBarSeries();
    series->append(set0);

    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique des region ");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;
    categories <<name[0]<<name[1]<<name[2]<<name[3]<<name[4];
    QBarCategoryAxis *axis=new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    QChartView *ChartView=new QChartView(chart);

     //ChartView->setParent(ui->horizontalFrame);
    //ui->stackedWidget->setCurrentIndex(2);

}


void MainWindow::on_statistique_clicked()

{
QBarSet *set0=new QBarSet("don");

int n1=0;
int n2=0;
int n3=0;
int n4=0;
int n5=0;
int n6=0;
int n7=0;
int n8=0;
int n9=0;
int n10=0;
 int n11=0;
 int n12=0;
don cp;
 QSqlQueryModel*  modal1=cp.countdon1("1");
qDebug()<<(n1=modal1->rowCount());
 modal1=cp.countdon1("2");
qDebug()<<(n2=modal1->rowCount());
 modal1=cp.countdon1("3");
qDebug()<<(n3=modal1->rowCount());
modal1=cp.countdon1("4");
qDebug()<<(n4=modal1->rowCount());
modal1=cp.countdon1("5");
qDebug()<<(n5=modal1->rowCount());
modal1=cp.countdon1("6");
qDebug()<<(n6=modal1->rowCount());
modal1=cp.countdon1("7");
qDebug()<<(n7=modal1->rowCount());
modal1=cp.countdon1("8");
qDebug()<<(n8=modal1->rowCount());
modal1=cp.countdon1("9");
qDebug()<<(n9=modal1->rowCount());
modal1=cp.countdon1("10");
qDebug()<<(n10=modal1->rowCount());
modal1=cp.countdon1("11");
qDebug()<<(n11=modal1->rowCount());
modal1=cp.countdon1("12");
qDebug()<<(n12=modal1->rowCount());
*set0<<n1<<n2<<n3<<n4<<n5<<n6<<n7<<n8<<n9<<n10<<n11<<n12;

QBarSeries *series=new QBarSeries();
series->append(set0);

QChart *chart=new QChart();
chart->addSeries(series);
chart->setTitle("Statistique des tickets vendus ");
chart->setAnimationOptions(QChart::SeriesAnimations);
QStringList categories;
categories <<"Janvier"<<"Fevrier"<<"Mars"<<"Avril"<<"Mai"<<"Juin"<<"Juillet"<<"Aout"<<"Septembre"<<"Octobre"<<"Novmbre"<<"Décembre";
QBarCategoryAxis *axis=new QBarCategoryAxis();
axis->append(categories);
chart->createDefaultAxes();
chart->setAxisX(axis,series);
QChartView *ChartView=new QChartView(chart);

 //ChartView->setParent(ui->horizontalFrame);
 //ui->stackedWidget->setCurrentIndex(2);

}



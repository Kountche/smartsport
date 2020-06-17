#include "email.h"
#include "smtp.h"
#include "ui_email.h"
#include "mainwindow.h"
#include<QMessageBox>
email::email(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::email)
{
    ui->setupUi(this);
    //smpt
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
}


//smtp


void email::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void email::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
//


email::~email()
{
    delete ui;
}

void email::on_pushButton_2_clicked()
{
    this->hide();
    ret1 =new MainWindow(this);
    ret1->show();
}


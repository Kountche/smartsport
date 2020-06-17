#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "email.h"
#include <QMainWindow>
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_ajouter_d_clicked();
    void on_afficher_d_clicked();
    void on_modifier_d_clicked();
    void on_supprimer_d_clicked();
    void on_imprimer_d_clicked();
    void on_fichier_d_clicked();
    void on_rechercher_d_clicked();
    void on_quitter_d_clicked();
    void on_pdf_d_clicked();
    void on_tableView_2_doubleClicked(const QModelIndex &index);
    void on_lineEdit_textChanged(const QString &arg1);
    void on_email_d_clicked();
    void on_tri_d_clicked();
    void on_afficherstat_clicked();


    void on_ajouter_1_clicked();
    void on_afficher_1_clicked();
    void on_modifier_1_clicked();
    void on_supprimer_1_clicked();
    void on_imprimer_1_clicked();
    void on_fichier_1_clicked();
    void on_rechercher_1_clicked();
    void on_quitter_1_clicked();
    void on_pdf_1_clicked();
    void on_tableView_e_doubleClicked(const QModelIndex &index);
    void on_lineEdit_1_textChanged(const QString &arg1);
    void on_email_1_clicked();
    void on_tri_1_clicked();
    void on_statistique_clicked();


    void on_commandLinkButton_clicked();
    void on_commandLinkButton_2_clicked();



private:
    Ui::MainWindow *ui;
    email *gemail;

};
#endif // MAINWINDOW_H

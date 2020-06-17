#ifndef EMAIL_H
#define EMAIL_H


#include <QMainWindow>
class MainWindow;

namespace Ui {
class email;
}

class email : public QMainWindow
{
    Q_OBJECT

public:
    explicit email(QWidget *parent = 0);
    ~email();

private slots:
    void on_pushButton_2_clicked();
    //smtp
    void sendMail();
    void mailSent(QString);




private:
    Ui::email *ui;
    MainWindow *ret1;
};

#endif // EMAIL_H

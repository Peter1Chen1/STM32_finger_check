#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QSerialPort>
#include <string.h>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

signals:
    void signal_return();

public slots:
    void recv_data();

private slots:
    void on_pushButton_return_clicked();

    void on_pushButton_input_clicked();

    void on_pushButton_identy_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_connect_clicked();


private:
    Ui::Home *ui;

    QSerialPort *serial;

    char buf[128];

    QSqlDatabase db;
};

#endif // HOME_H

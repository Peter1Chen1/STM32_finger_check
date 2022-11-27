#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include "home.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    //信号只有声明
    void signal_id_passwd(QString id,QString passwd);

public slots:
    void slot_id_passwd(QString id,QString passwd);
    void slot_return();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::Widget *ui;
    Home *h;
};
#endif // WIDGET_H

#include "widget.h"
#include "ui_widget.h"




Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    h = new Home;

    qDebug()<<"hello world";

    //自定义信号和自定义槽函数的手动连接
    connect(this,SIGNAL(signal_id_passwd(QString,QString)),this,SLOT(slot_id_passwd(QString,QString)));
    connect(h,SIGNAL(signal_return()),this,SLOT(slot_return()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slot_id_passwd(QString id, QString passwd)
{
    if(id == "peter" && passwd == "123456")
    {
        qDebug()<<"登录成功！";
        //主界面显示出来
        h->show();
        //登录界面关闭
        this->close();
    }
    else
    {
        qDebug()<<"登录失败";
    }
}

void Widget::slot_return()
{
    h->close();
    delete h;
    this->show();
}


void Widget::on_pushButton_login_clicked()
{
    //text():获取控件上的文本信息
    QString id = ui->lineEdit_id->text();
    QString passwd = ui->lineEdit_passwd->text();

    emit this->signal_id_passwd(id,passwd);

    //qDebug()<<"id："<<id;
    //qDebug()<<"on_pushButton_login_clicked()";
}

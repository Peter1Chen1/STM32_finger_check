#include "home.h"
#include "ui_home.h"

#include <QEventLoop>
#include <QTimer>



void delay_msec(unsigned int msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec,&loop,SLOT(quit()));
    loop.exec();
}

Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    serial = new QSerialPort;

    connect(serial,SIGNAL(readyRead()),this,SLOT(recv_data()));

    if(QSqlDatabase::contains("qt_sql_defult_connection") == true)
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("test_database.db");
    }

    if(db.open() == true)
    {
        ui->textEdit->insertPlainText("数据库打开成功\n");
    }
    else
    {
        ui->textEdit->insertPlainText("数据库打开失败\n");
    }

    QSqlQuery query(db);
//    if(query.exec("select count(*) from sqlite_master where type = 'table' and name = 'test_table'") == true)
//    {
//       ui->textEdit->insertPlainText("test_table 已经存在\n");
//    }
//    else
//    {
//       ui->textEdit->insertPlainText("test_table 不存在\n");
         if(query.exec("create table test_table(id test,name test,time test)") == true)
         {
            ui->textEdit->insertPlainText("test_table 创建成功\n");
         }
         else
         {
            ui->textEdit->insertPlainText("test_table 创建失败\n");
            qDebug()<<"test_table 创建失败:"<<query.lastError();
         }
//     }
}

Home::~Home()
{
    delete ui;
}

void Home::recv_data()
{
    QByteArray data = serial->readAll();
    //qDebug()<<"recv_data:"<<data;

    ui->textEdit->insertPlainText(data);
    //将开发板通过串口上传的数据显示到文本编辑框中

    QSqlQuery query(db);
    if(query.exec("select * from test_table") == true)
    {
        while(query.next())
        {
            if(QString::number(data.toInt())== query.value(0).toString())
            {
                ui->textEdit->insertPlainText(query.value(1).toString());
                ui->textEdit->insertPlainText("\n");
                return ;
            }
        }
        ui->textEdit->insertPlainText("id 不存在\n");
        return ;
     }
     else
     {
        qDebug()<<"Search fail:"<<query.lastError();
        return ;
     }
}

void Home::on_pushButton_return_clicked()
{
    emit this->signal_return();
}


void Home::on_pushButton_input_clicked()
{
    QSqlQuery query(db);
    query.prepare("insert into test_table values(?,?,?)");
    query.addBindValue("1");
    query.addBindValue("Tom");
    query.addBindValue("10:13");

    if(query.exec() == true)
    {
        ui->textEdit->insertPlainText("注册成功\n");
    }
    else
    {
        ui->textEdit->insertPlainText("注册失败\n");
    }

    query.prepare("insert into test_table values(?,?,?)");
    query.addBindValue("2");
    query.addBindValue("Jerry");
    query.addBindValue("10:13");

    if(query.exec() == true)
    {
        ui->textEdit->insertPlainText("注册成功\n");
    }
    else
    {
        ui->textEdit->insertPlainText("注册失败\n");
    }


}

void Home::on_pushButton_identy_clicked()
{
    memset(buf,0,sizeof(buf));
    buf[0] = '3';//'3',检测指纹
    serial->write(buf,strlen(buf));
}

void Home::on_pushButton_delete_clicked()
{
//    ui->pushButton_input->setStyleSheet();
//    delay_msec(200);
//    ui->pushButton_input->setStyleSheet();
}

void Home::on_pushButton_connect_clicked()
{
    //获取组合编辑框当前选中的文本
    QString com = ui->comboBox->currentText();

    serial->setPortName(com);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setParity(QSerialPort::NoParity);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setReadBufferSize(1024);
    serial->open(QIODevice::ReadWrite);
    serial->open(QSerialPort::ReadWrite);

//    memset(buf,0,sizeof(buf));
//    buf[0] = '1';//'1',测试连接
//    serial->write(buf,strlen(buf));
}



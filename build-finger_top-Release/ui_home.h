/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Home
{
public:
    QPushButton *pushButton_return;
    QTextEdit *textEdit;
    QPushButton *pushButton_input;
    QPushButton *pushButton_identy;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_connect;
    QComboBox *comboBox;

    void setupUi(QWidget *Home)
    {
        if (Home->objectName().isEmpty())
            Home->setObjectName(QStringLiteral("Home"));
        Home->resize(590, 430);
        Home->setStyleSheet(QStringLiteral(""));
        pushButton_return = new QPushButton(Home);
        pushButton_return->setObjectName(QStringLiteral("pushButton_return"));
        pushButton_return->setGeometry(QRect(430, 350, 100, 30));
        pushButton_return->setStyleSheet(QStringLiteral("font: 10pt \"Microsoft YaHei UI\";"));
        textEdit = new QTextEdit(Home);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(20, 110, 371, 301));
        textEdit->setStyleSheet(QStringLiteral("font: 10pt \"Microsoft YaHei UI\";"));
        pushButton_input = new QPushButton(Home);
        pushButton_input->setObjectName(QStringLiteral("pushButton_input"));
        pushButton_input->setGeometry(QRect(420, 50, 120, 35));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_input->sizePolicy().hasHeightForWidth());
        pushButton_input->setSizePolicy(sizePolicy);
        pushButton_input->setStyleSheet(QStringLiteral("font: 10pt \"Microsoft YaHei UI\";"));
        pushButton_identy = new QPushButton(Home);
        pushButton_identy->setObjectName(QStringLiteral("pushButton_identy"));
        pushButton_identy->setGeometry(QRect(420, 150, 120, 35));
        sizePolicy.setHeightForWidth(pushButton_identy->sizePolicy().hasHeightForWidth());
        pushButton_identy->setSizePolicy(sizePolicy);
        pushButton_identy->setStyleSheet(QStringLiteral("font: 10pt \"Microsoft YaHei UI\";"));
        pushButton_delete = new QPushButton(Home);
        pushButton_delete->setObjectName(QStringLiteral("pushButton_delete"));
        pushButton_delete->setGeometry(QRect(420, 250, 120, 35));
        sizePolicy.setHeightForWidth(pushButton_delete->sizePolicy().hasHeightForWidth());
        pushButton_delete->setSizePolicy(sizePolicy);
        pushButton_delete->setStyleSheet(QStringLiteral("font: 10pt \"Microsoft YaHei UI\";"));
        pushButton_connect = new QPushButton(Home);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setGeometry(QRect(230, 50, 120, 35));
        pushButton_connect->setStyleSheet(QStringLiteral("font: 10pt \"Microsoft YaHei UI\";"));
        comboBox = new QComboBox(Home);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEnabled(true);
        comboBox->setGeometry(QRect(30, 50, 120, 35));
        comboBox->setStyleSheet(QStringLiteral("font: 10pt \"Microsoft YaHei UI\";"));

        retranslateUi(Home);

        QMetaObject::connectSlotsByName(Home);
    } // setupUi

    void retranslateUi(QWidget *Home)
    {
        Home->setWindowTitle(QApplication::translate("Home", "Form", Q_NULLPTR));
        pushButton_return->setText(QApplication::translate("Home", "back", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        pushButton_input->setText(QApplication::translate("Home", "finger input", Q_NULLPTR));
        pushButton_identy->setText(QApplication::translate("Home", "finger identy", Q_NULLPTR));
        pushButton_delete->setText(QApplication::translate("Home", "finger delete", Q_NULLPTR));
        pushButton_connect->setText(QApplication::translate("Home", "connect", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Home", "COM3", Q_NULLPTR)
         << QApplication::translate("Home", "COM4", Q_NULLPTR)
         << QApplication::translate("Home", "COM6", Q_NULLPTR)
         << QApplication::translate("Home", "COM8", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class Home: public Ui_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H

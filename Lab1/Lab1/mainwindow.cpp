#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QJsonDocument>
#include <windows.h>
#include <QProcess>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pass = new KeyManager;
    //Скрываем сообщение об ошибке
    ui->label_error->setVisible(false);
    // Label который выдает предупреждение, что работает отладчик
    ui->label_debug->setVisible(false);
    connect(pass, &KeyManager::ShowMW,this,&MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{


    ui->pincode->setVisible(true);
    // В переменную код считываем введенный пин код, если он верный то открываем файл с кредами
    // и перекидываем на новое окно. Если неверный, то отображаем соответствующий label
    QString code;
    code = ui->pincode->text();
    if (code == "1567")
    {
        this->close();
        pass->open_pass();
        pass->show();
        pass->createUI(QStringList()
                        << tr("Id")
                        << tr("Site")
                        << tr("Login")
                        << tr("Password")
      );

    }
    else
    {
        ui->label_error->setVisible(true);
    }

}

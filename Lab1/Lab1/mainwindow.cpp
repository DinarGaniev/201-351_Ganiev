#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "keymanager.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    KeyManager window;
    QString pincode = "1567";
    if (ui->pincode->text() == pincode)
    {
        this->close();
        window.setModal(true);
        window.exec();
    }
    else
    {
        QMessageBox::warning(this,"Авторизация","Введен неправильный пин-код. Повторите попытку");
    }
}


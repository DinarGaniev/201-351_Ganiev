#include "keymanager.h"
#include "ui_keymanager.h"
#include <QClipboard>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QApplication>

//"C:\201-351_Ganiev\Lab1\Lab1\data.json"


KeyManager::KeyManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyManager)
{
    ui->setupUi(this);


    load();
}

KeyManager::~KeyManager()
{
    delete ui;
}

void KeyManager::load()
{

    QFile jsonFile(QDir::toNativeSeparators(QApplication::applicationDirPath()) + "\\data.json"); // Создаю  переменную файла
    //QFile jsonFile("C:/201-351_Ganiev/Lab1/Lab1/data.json");
    if (!jsonFile.open(QIODevice::ReadOnly ))
        {
            return;
        }
    QByteArray saveData = jsonFile.readAll(); // Считываю файл
    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData)); // Создаём QJsonDocument
    JsonDoc = jsonDocument.object(); // Перетаскиваю объект в переменную QJsonObject
    jsonFile.close();


    ui->tableWidget->setRowCount(0);
    for (int var = 0; var < JsonDoc.value("creds").toArray().count(); var++) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        QTableWidgetItem *site = new QTableWidgetItem(JsonDoc.value("creds")[var].toObject().value("site").toString());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, site);

        QTableWidgetItem *login = new QTableWidgetItem;
        login->setData(Qt::UserRole, JsonDoc.value("creds")[var].toObject().value("login").toString());
        login->setText("*****");
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, login);

        QTableWidgetItem *pass = new QTableWidgetItem;
        pass->setData(Qt::UserRole, JsonDoc.value("creds")[var].toObject().value("pass").toString());
        pass->setText("********");
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, pass);
    }
}

void KeyManager::on_pushButton_clicked()
{
    for (int var = 0; var < ui->tableWidget->rowCount(); ++var) {
        if(ui->tableWidget->verticalHeaderItem(var)->text().contains(ui->lineEdit->text(), Qt::CaseInsensitive)==0)
        {
            ui->tableWidget->removeRow(var);
            on_pushButton_clicked();
        }

    }
}

void KeyManager::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString text = ui->tableWidget->item(row,column)->data(Qt::UserRole).toString();
    QApplication::clipboard()->setText(text);
}


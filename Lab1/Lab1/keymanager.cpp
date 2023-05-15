#include "keymanager.h"
#include "ui_keymanager.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>
#include <QCoreApplication>
#include <QDir>
#include <QItemDelegate>
#include <iostream>
#include <QClipboard>
#include <QCryptographicHash>
//"C:\201-351_Ganiev\Lab1\Lab1\data.json"


KeyManager::KeyManager(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::KeyManager)
{
    ui->setupUi(this);
}

//функция хэширования
std::string KeyManager::converthash_key(){
    QString kod = "1567";
    QByteArray hash = QCryptographicHash::hash
            (kod.toUtf8(),
             QCryptographicHash::Sha256);
    hash = hash.toBase64();
    QString m = QString((char *)hash.data());
    std::string str_hash = m.toStdString();
    return str_hash;
}


void KeyManager::encr_log_pass_and_file(){

    QFile jsonFile("data.json"); // Создаю  переменную файла
    if (!jsonFile.open(QIODevice::ReadOnly ))
    {
        return;
    }
    QByteArray saveData = jsonFile.readAll(); // Считываю файл
    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData)); // Создаём QJsonDocument

    // получаем хеш ключа
    std::string key_pin = converthash_key();

    KeyManager1 = jsonDocument.object();
    KeyManagerArray1 = KeyManager1["cridentials"].toArray();



    QJsonArray Cridentials;

    for (const QJsonValue & str : KeyManagerArray1)
    {
        if (str.isObject())
        {
            //Считываем значение объекта json файла и записываем в переменные Qstring
            QJsonObject obj = str.toObject();
            QString site = obj["site"].toString();
            QString login = obj["login"].toString();
            QString password = obj["password"].toString();

            // переводим кодировку в string
            std::string login_new = login.toUtf8().constData();
            std::string password_new = password.toUtf8().constData();

            std::vector<std::string> crid_new;
            crid_new.push_back("\"login\":\"");
            crid_new.push_back(login_new);
            crid_new.push_back("\",\"password\":\"");
            crid_new.push_back(password_new);
            crid_new.push_back("\"");

            // преобразования std::vector к std::string разделенные разделителем,
            //использует строковый поток
            std::stringstream str;
            for (auto it = crid_new.begin(); it != crid_new.end(); it++)    {
                if (it != crid_new.begin()) {
                    str << "";
                }
                str << *it;
            }
            std::string str_crid_new = str.str();
            //std::cout << ss.str() << std::endl;

            //шифруем слепленные логины и пароли
            std::string encr_crid_new = aes_json->encrypt_obj(key_pin, str_crid_new);

            // преобразуем обратно в Qstring для работы с json
            QString encr_qstr_crid_new = QString::fromStdString(encr_crid_new);

            QJsonObject PassManagerObject;

            PassManagerObject.insert("site", site);
            PassManagerObject.insert("crid_new", encr_qstr_crid_new);


            Cridentials.append(PassManagerObject);
            }
    }

    //На данном этапе у нас зашифрованы логины и пароли

    // создаем новую json структуру
    QJsonObject new_log_pass_json;
    new_log_pass_json.insert("cridentials", QJsonValue(Cridentials));

    QJsonDocument doc(new_log_pass_json);

    //конвертация json в Qstring (из документации)
    QString new_qstring_log_pass_json(doc.toJson(QJsonDocument::Compact));


    //шифруем весь файл
    //конвертация Qstring в string
    std::string new_string_log_pass_json = new_qstring_log_pass_json.toUtf8().constData();
    aes_json->encrypt_file(key_pin, new_string_log_pass_json);

}

void KeyManager::open_pass(){

    //вызываем функцию шифрования логинов и паролей
    encr_log_pass_and_file();
    QFile file("data_new.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

//    избавляемся от кодировки Base64
    QByteArray buffer = QByteArray::fromBase64(file.readAll());
    std::vector<uint8_t> data(buffer.begin(), buffer.end());

    // получаем хэш ключа
    std::string key_pin = converthash_key();
    //расшифровываем содержимое файла в переменную for_parsing
    std::string for_parsing = aes_json->decrypt(key_pin, data);
    qDebug() << QString::fromStdString(for_parsing);


    //конвертация в QString
    QString parsed_json = QString::fromUtf8(for_parsing.c_str());

    QJsonParseError error;
    doc1 = QJsonDocument::fromJson(parsed_json.toUtf8(), &error);
    KeyManager1 = doc1.object();
    KeyManagerArray1 = KeyManager1["cridentials"].toArray();

}


void KeyManager::createUI(const QStringList &headers){
    ui->tableWidget->setColumnCount(4); // Указываем число колонок
    ui->tableWidget->setShowGrid(true); // Включаем сетку
    // Разрешаем выделение только одного элемента
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем заголовки колонок
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    // Скрываем колонку под номером 0
    ui->tableWidget->hideColumn(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed);
    QString search_site = "";
    cridentials(search_site);
}

// расшифровываем нашу структуру crid которая состоит из слепленных логинов и паролей
QJsonArray KeyManager::decrypted_crid(QLineEdit* lineEdit) {

    QString crids = lineEdit->text();

    std::string crids_string = crids.toStdString();
    const char *crids_char = crids_string.c_str();

    //избавляемся от кодировки Base64
    QByteArray buffer = QByteArray::fromBase64(crids_char);
    std::vector<uint8_t> data(buffer.begin(), buffer.end());

    // получаем хеш ключа
    std::string key_pin = converthash_key();
    //расшифровывываем логины и пароли
    std::string crids_decrypt = aes_json->decrypt(key_pin, data);

    QString crids_decrypt2 = QString::fromStdString(crids_decrypt);

    //qDebug() << crids_decrypt2;
    std::string crids_decrypt_str = crids_decrypt2.toStdString();

    //std::cout << crids_decrypt_str << std::endl;

    //записываем логины и пароль в новую подобную-json стркутуру
    std::vector<std::string> crid_new2;
    crid_new2.push_back("{\"crids\":[{");
    crid_new2.push_back(crids_decrypt_str);
    crid_new2.push_back("}]}");

    // преобразования std::vector к std::string разделенные разделителем,
    //использует строковый поток
    std::stringstream str;
    for (auto it = crid_new2.begin(); it != crid_new2.end(); it++)    {
        if (it != crid_new2.begin()) {
            str << "";
        }
        str << *it;
    }
    std::string str_crid_new2 = str.str();
    QString qstr_str_crid_new2 = QString::fromStdString(str_crid_new2);


    QJsonParseError error;
    doc2 = QJsonDocument::fromJson(qstr_str_crid_new2.toUtf8(), &error);
    KeyManager2 = doc2.object();
    KeyManagerArray2 = KeyManager2["crids"].toArray();
    return KeyManagerArray2;
}

//функция qlineedit для отслеживания кликов
bool KeyManager::eventFilter(QObject* watched, QEvent* event)
{
    //если был клик на ячейку, то расшифровываем логин и пароль
    // копируем в буфер
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(QLineEdit* lineEdit = qobject_cast<QLineEdit*>(watched))
        {
            Q_FOREACH(const QLineEdit* i, findChildren<QLineEdit*>())
            i->disconnect();

            // для понимания, что клик на нужную ячуйку(логин или пароль)
            int column = lineEdit->property("column").toInt();

            // если кликнули не на сайт
            if (column != 1)
            {
            //расшифровываем данные из этой ячейки
            QJsonArray PassManagerArray = decrypted_crid(lineEdit);

            //в click будем хранить данные из буфера
            QClipboard *click = QGuiApplication::clipboard();

            // если логин
            if (column == 2) {
                for (const QJsonValue & str : PassManagerArray)
                {
                     if (str.isObject())
                     {
                         QJsonObject obj = str.toObject();
                         QString login = obj["login"].toString();
                         //запись в буфер
                         click->setText(login);
                      }
                 }
            }
            // если пароль
            else if (column == 3) {
                for (const QJsonValue & str : PassManagerArray)
                {
                     if (str.isObject())
                     {
                         QJsonObject obj = str.toObject();
                         QString password = obj["password"].toString();
                         //запись в буфер
                         click->setText(password);
                      }
                 }
            }
            }
        }
    }
    return QObject::eventFilter(watched, event);
}


void KeyManager::cridentials(QString search_site) {
        ui->tableWidget->setRowCount(0); //очищаем поле поиска
        QString array;
        int i = 0;
        for (const QJsonValue & str : KeyManagerArray1)
        {
            if (str.isObject())
            {
                //Считываем значение объекта json файла и записываем в переменные Qstring
                QJsonObject obj = str.toObject();

                QString site = obj["site"].toString();
                QString crids = obj["crid_new"].toString();

                // Текст, который ввел пользователь, при поиске
                QString search = search_site;
                // Преобразуем данные Qstring в string
                std::string string_search = search.toUtf8().constData();
                std::string string_site = site.toUtf8().constData();

                //ищем подстроку в строке, для поиска
                int pos = string_site.find(string_search);

                //qDebug() << i << site << login << password << pos;

                if (pos > -1) {
                    ui->tableWidget->insertRow(i);

                    QLineEdit *lineEdit_site = new QLineEdit(site);
                    QLineEdit *lineEdit_login = new QLineEdit(crids);
                    QLineEdit *lineEdit_password = new QLineEdit(crids);

                    // для сайта
                    lineEdit_site->setProperty("column", 1);
                    lineEdit_site->setReadOnly(true);
                    //чтобы отследить что выбрана ячейка
                    lineEdit_site->installEventFilter(this);

                    // для логина
                    lineEdit_login->setProperty("column", 2);
                    lineEdit_login->setReadOnly(true);
                    //чтобы отследить что выбрана ячейка
                    lineEdit_login->installEventFilter(this);

                    //для пароля
                    lineEdit_password->setProperty("column", 3);
                    lineEdit_password->setReadOnly(true);
                    //чтобы отследить что выбрана ячейка
                    lineEdit_password->installEventFilter(this);


                    //Отображаем в виде слепых символов логин
                    lineEdit_login->setEchoMode(QLineEdit::Password);

                    //Отображаем в виде слепых символов пароль
                    lineEdit_password->setEchoMode(QLineEdit::Password);

                    //отображаем результаты поиска
                    ui->tableWidget->setCellWidget(i, 1, lineEdit_site);
                    ui->tableWidget->setCellWidget(i, 2, lineEdit_login);
                    ui->tableWidget->setCellWidget(i, 3, lineEdit_password);
                    i++;
                }
           }
     }
}

// кнопка поиска
void KeyManager::on_pushButton_clicked()
{
    // считываем что ввел пользователь, при поиске
    QString search_site = ui->pushButton->text();
    qDebug() << search_site;
    cridentials(search_site);
}


KeyManager::~KeyManager()
{
    delete ui;
}


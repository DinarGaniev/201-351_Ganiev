#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "cryptocontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class KeyManager; }
QT_END_NAMESPACE

class KeyManagerData;

class KeyManager : public QDialog
{
    Q_OBJECT

public:
    KeyManager(QWidget *parent = nullptr);
    ~KeyManager();
    void open_pass();
    void createUI(const QStringList &headers);
    std::string converthash_key();



private:
    Ui::KeyManager *ui;
    cryptcontroller *aes_json;
    void cridentials(QString search_site);
    void encr_log_pass_and_file();
    QJsonArray decrypted_crid(QLineEdit* lineEdit);
    bool eventFilter(QObject* watched, QEvent* event);
    QJsonDocument doc1;
    QJsonObject KeyManager1;
    QJsonArray KeyManagerArray1;
    QJsonDocument doc2;
    QJsonObject KeyManager2;
    QJsonArray KeyManagerArray2;

signals:
    void ShowMW();

private slots:
    void on_pushButton_clicked();
};

#endif// KEYMANAGER_H

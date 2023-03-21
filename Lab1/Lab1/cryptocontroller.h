#ifndef CRYPTOCONTROLLER_H
#define CRYPTOCONTROLLER_H

#include <QObject>

class CryptoController : public QObject
{
    Q_OBJECT
public:
    explicit CryptoController(QObject *parent = nullptr);
    // проверки пин-кода

    // метод для расшифровки файла учетных данных
    bool decrypt_file(
            const QString & filename,
            const QByteArray & key);

    bool decrypt_record(
           const QByteArray & encryptedrecord,
            QByteArray & login,
            QByteArray & password);


signals:

};

#endif // CRYPTOCONTROLLER_H

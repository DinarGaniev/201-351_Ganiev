#include "cryptocontroller.h"

CryptoController::CryptoController(QObject *parent)
    : QObject{parent}
{

}

bool CryptoController::decrypt_file(const QString &filename, const QByteArray &key)
{
    return false;
}

bool CryptoController::decrypt_record(const QByteArray &encryptedrecord, QByteArray &login, QByteArray &password)
{
    return false;
}

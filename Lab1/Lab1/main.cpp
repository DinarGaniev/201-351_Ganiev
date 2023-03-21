#include "mainwindow.h"
#include <QApplication>
#include <QGuiApplication>
#include "mainwindow.h"
#include <QCryptographicHash>
#include <Windows.h>
#include <iostream>
#include <intrin.h>
#include <QProcess>
#include <QtWidgets/QMessageBox>
#include <QMessageBox>
#include "cryptocontroller.h"

typedef unsigned long long QWORD;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 5 задание
    // Проверка хэша
    QWORD moduleBase = (QWORD)GetModuleHandle(NULL);
    QWORD text_segment_start = moduleBase + 0x1000;


    PIMAGE_DOS_HEADER pIDH = reinterpret_cast<PIMAGE_DOS_HEADER>(moduleBase);
    PIMAGE_NT_HEADERS pINH = reinterpret_cast<PIMAGE_NT_HEADERS>(moduleBase + pIDH->e_lfanew);
    QWORD size_of_text = pINH->OptionalHeader.SizeOfCode;

    QByteArray text_segment_contents = QByteArray((char*)text_segment_start, size_of_text);
    QByteArray current_hash = QCryptographicHash::hash(text_segment_contents, QCryptographicHash::Sha256);
    QByteArray current_hash_base64 = current_hash.toBase64();

    const QByteArray hash0_base64 = QByteArray("/r6pzG/g7J+zeyFBX32QHuiBMWRDgzGw3gQlyQnZNrA=");
    const QByteArray hash0_base64_debug = QByteArray("xdEYaue6fn6OvmqAptEZy2DEAheVTjbnDmlX6Z0w1rs=");


    qDebug() << "text_segment_start= " << Qt::hex << text_segment_start;
    qDebug() << "size_of_text= " << size_of_text;
    qDebug() << "text_segment_contents= " << Qt::hex << text_segment_contents.first(100);
    qDebug() << "current_hash_base64= " << current_hash_base64;

    bool checkresult = true;
//    bool checkresult = (current_hash_base64==hash0_base64 or current_hash_base64==hash0_base64_debug);
    qDebug() << "checkresult= " << checkresult;
    if(!checkresult) {
        QMessageBox::critical(nullptr, "Внимание!", "Приложение модифицированно!");
        qDebug() << "Внимание! Приложение модифицированно!";
        return -1;
    }

    // 3 задание
    //Блок простейшего отладчика
//    bool debuggerFound = IsDebuggerPresent();
//    if(debuggerFound) {
//        QMessageBox::critical(nullptr, "Внимание!", "Найден активный дебаггер!");
//        qDebug() << "Найден активный дебаггер!";
//        std::cout << "Найден активный дебаггер";
//        return -1;
//    }

    // 4 задание
    //Блок защиты от отладки самоотладкой
    QProcess *satelliteProcess = new QProcess();
    int pid = QGuiApplication::applicationPid();
    qDebug() << "pid = " << pid;
    QStringList arguments = {QString::number(pid)};
    qDebug() << "arguments = " << arguments;
    satelliteProcess->start("DebugProtector.exe", arguments);
    bool protectorStarted = satelliteProcess->waitForStarted(1000);
    qDebug() << "protectorStarted = " << protectorStarted;
    MainWindow w;
    w.show();
    return a.exec();
}

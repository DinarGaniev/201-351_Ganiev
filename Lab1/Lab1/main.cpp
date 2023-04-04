#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <windows.h>
#include <QMessageBox>
#include <QProcess>

typedef unsigned long long QWORD;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // 5 задание
    // Проверка хэша
    unsigned long long moduleBase = (unsigned long long)GetModuleHandle(NULL);// определяем смещение в виртуальной где расположен сегмент
    unsigned long long text_segment_start = moduleBase + 0x1000; //адрес сегмента .text
    // определяем какой он длины (парсим заголовки)
    PIMAGE_DOS_HEADER pIDH = reinterpret_cast<PIMAGE_DOS_HEADER>(moduleBase);
    PIMAGE_NT_HEADERS pINH = reinterpret_cast<PIMAGE_NT_HEADERS>(moduleBase+ pIDH->e_lfanew);
    unsigned long long size_of_text = pINH->OptionalHeader.SizeOfCode; //размер сегмента .text
    // выгружаем содержимое контейнера в QByteArray
    QByteArray text_segment_contents = QByteArray((char*)text_segment_start, size_of_text);
    // считаем хеш
    QByteArray current_hash =
            QCryptographicHash::hash(text_segment_contents, QCryptographicHash::Sha256);
    QByteArray current_hash_base64 = current_hash.toBase64();

    qDebug() << "current_hash_base64 = " << current_hash_base64;
    // сравниваем полученный хеш с эталонным

    const QByteArray hash0_base64 = QByteArray("cpimSClNRw2rZsWqi5b6Pny+NJL5zJVWgGwNBLLAuXg=");
    const QByteArray hash0_base64_debug = QByteArray("xdEYaue6fn6OvmqAptEZy2DEAheVTjbnDmlX6Z0w1rs=");


    if (current_hash_base64!=hash0_base64_debug and current_hash_base64!=hash0_base64)
    {
    QMessageBox::critical(nullptr, "Внимание!", "Приложение модифицированно!");
    qDebug() << "stop";
    Sleep(5000);
    }
    else
    {
//        //Проверяем выполняется ли отладка
//        if (IsDebuggerPresent())
//        {
//            ui->debug->setVisible(true);
//        }
//        else
//        {
    w.show();
    return a.exec();
//        }
    }
}

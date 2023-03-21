#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <QDialog>
#include <QJsonObject>

namespace Ui {
class KeyManager;
}

class KeyManager : public QDialog
{
    Q_OBJECT

public:
    explicit KeyManager(QWidget *parent = nullptr);
    ~KeyManager();
    QJsonObject JsonDoc;

private slots:
    void on_pushButton_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);

public slots:
    void load();

private:
    Ui::KeyManager *ui;
};

#endif // KEYMANAGER_H

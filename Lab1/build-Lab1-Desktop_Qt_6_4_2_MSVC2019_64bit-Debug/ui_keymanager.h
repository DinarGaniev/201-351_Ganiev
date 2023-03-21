/********************************************************************************
** Form generated from reading UI file 'keymanager.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYMANAGER_H
#define UI_KEYMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_KeyManager
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QTableWidget *tableWidget;

    void setupUi(QDialog *KeyManager)
    {
        if (KeyManager->objectName().isEmpty())
            KeyManager->setObjectName("KeyManager");
        KeyManager->resize(395, 580);
        verticalLayout = new QVBoxLayout(KeyManager);
        verticalLayout->setObjectName("verticalLayout");
        lineEdit = new QLineEdit(KeyManager);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(KeyManager);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        tableWidget = new QTableWidget(KeyManager);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setColumnCount(3);
        tableWidget->horizontalHeader()->setMinimumSectionSize(39);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(true);
        tableWidget->verticalHeader()->setMinimumSectionSize(30);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(tableWidget);


        retranslateUi(KeyManager);

        QMetaObject::connectSlotsByName(KeyManager);
    } // setupUi

    void retranslateUi(QDialog *KeyManager)
    {
        KeyManager->setWindowTitle(QCoreApplication::translate("KeyManager", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("KeyManager", "\320\235\320\260\320\271\321\202\320\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("KeyManager", "Site", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("KeyManager", "Login", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("KeyManager", "Password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KeyManager: public Ui_KeyManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYMANAGER_H

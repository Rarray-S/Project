#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include "addokei.h"
#include "addbank.h"
#include "addcontract.h"
#include "addspecification.h"
#include "addgoods.h"
#include <QMessageBox>

QSqlDatabase MainWindow::db;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL", "mydb");
    db.setHostName("localhost");
    db.setDatabaseName("project_db");
    db.setUserName("root");
    db.setPassword("6h336R4pRCC2");
    db_open = db.open();
    if (db_open) {
        ui->statusbar->showMessage("База данных успешно подключена.", 5000);
        on_tabWidget_currentChanged(0);
    }
    else ui->statusbar->showMessage("Ошибка: Невозможно подключиться к базе данных.", 5000);
    ui->addGoods->setVisible(false);
    ui->removeGoods->setVisible(false);
    ui->updateGoods->setVisible(false);
    ui->table_Spec->setColumnHidden(0, true);
    ui->table_Goods->setColumnHidden(0, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    QSqlQuery query(db);
    int row;
    switch (index) {
    case 0:
        ui->Docx->setVisible(true);
        ui->toDocx->setVisible(true);
        ui->Spec_label->setVisible(true);
        ui->addSpec->setVisible(true);
        ui->addGoods->setVisible(false);
        ui->removeGoods->setVisible(false);
        ui->updateGoods->setVisible(false);
        ui->table_BIK->setRowCount(0);
        ui->table_Spec->setRowCount(0);
        ui->table_OKEI->setRowCount(0);
        row = ui->table_Contracts->rowCount();
        query.exec("SELECT Contract_number, Date_of_conclusion, Organization, Representative, Footing, Legal_address, OGRN, INN, KPP, BIK, Pay_account FROM Contracts");
        while (query.next()) {
             ui->table_Contracts->insertRow(row);
             for (int i = 0; i < 11; i++)
             ui->table_Contracts->setItem(row, i, new QTableWidgetItem(query.value(i).toString()));
             row++;
        }
        ui->table_Contracts->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    break;
    case 1:
        ui->Docx->setVisible(true);
        ui->toDocx->setVisible(true);
        ui->Spec_label->setVisible(true);
        ui->addSpec->setVisible(false);
        ui->addGoods->setVisible(true);
        ui->removeGoods->setVisible(true);
        ui->updateGoods->setVisible(true);
        ui->table_BIK->setRowCount(0);
        ui->table_Contracts->setRowCount(0);
        ui->table_OKEI->setRowCount(0);
        row = ui->table_Spec->rowCount();
        query.exec("SELECT * FROM specificanion");
        while (query.next()) {
             ui->table_Spec->insertRow(row);
             ui->table_Spec->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
             ui->table_Spec->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
             ui->table_Spec->setItem(row, 2, new QTableWidgetItem(query.value(3).toString()));
             ui->table_Spec->setItem(row, 3, new QTableWidgetItem(query.value(2).toString()));
             row++;
        }
        ui->table_Spec->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    break;
    case 2:
        ui->Docx->setVisible(false);
        ui->toDocx->setVisible(false);
        ui->Spec_label->setVisible(false);
        ui->addSpec->setVisible(false);
        ui->addGoods->setVisible(false);
        ui->removeGoods->setVisible(false);
        ui->updateGoods->setVisible(false);
            ui->table_Contracts->setRowCount(0);
            ui->table_Spec->setRowCount(0);
            ui->table_OKEI->setRowCount(0);
            row = ui->table_BIK->rowCount();
            query.exec("SELECT * FROM Bank");
            while (query.next()) {
                 ui->table_BIK->insertRow(row);
                 ui->table_BIK->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
                 ui->table_BIK->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
                 ui->table_BIK->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
                 row++;
            }
            ui->table_BIK->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
        break;
    case 3:
        ui->Docx->setVisible(false);
        ui->toDocx->setVisible(false);
        ui->Spec_label->setVisible(false);
        ui->addSpec->setVisible(false);
        ui->addGoods->setVisible(false);
        ui->removeGoods->setVisible(false);
        ui->updateGoods->setVisible(false);
        ui->table_Contracts->setRowCount(0);
        ui->table_Spec->setRowCount(0);
        ui->table_BIK->setRowCount(0);
            row = ui->table_OKEI->rowCount();
            query.exec("SELECT * FROM OKEI");
            while (query.next()) {
                 ui->table_OKEI->insertRow(row);
                 ui->table_OKEI->setItem(row, 1, new QTableWidgetItem(query.value(0).toString()));
                 ui->table_OKEI->setItem(row, 0, new QTableWidgetItem(query.value(1).toString()));
                 ui->table_OKEI->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
                 row++;
            }
            ui->table_OKEI->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
        break;
    }
}


void MainWindow::on_addRecord_clicked()
{
    QSqlQuery query(db);
    QStringList add;
    int row, index = ui->tabWidget->currentIndex();
    if (index == 0) {
        addContract ContractDialog(&add);
        ContractDialog.exec();
        if (add.empty()) return;
        if (query.exec("INSERT INTO Contracts (Contract_number, Date_of_conclusion, Organization, Representative, Footing, Legal_address, OGRN, INN, KPP, BIK, Pay_account) "
                       "VALUES ('"+add[0]+"', '"+ add[1]+ "', '"+ add[2]+ "', '"+ add[3] + "', '"+ add[4] + "', '"+ add[5] + "', "+ add[6] + ", "+ add[7] + ", "+ add[8] + ", '"+ add[9] + "', '"+ add[10] + "')")) {
            ui->table_Contracts->setRowCount(0);
            row = 0;
            query.exec("SELECT Contract_number, Date_of_conclusion, Organization, Representative, Footing, Legal_address, OGRN, INN, KPP, BIK, Pay_account FROM Contracts");
            while (query.next()) {
                 ui->table_Contracts->insertRow(row);
                 for (int i = 0; i < 11; i++)
                 ui->table_Contracts->setItem(row, i, new QTableWidgetItem(query.value(i).toString()));
                 row++;
            }
        } else QMessageBox::critical(this, "Внимание!","При попытке добавления произошла ошибка.\nУбедитесь, что форма заполнена правильно!");
    }
    else if (index == 1) {
        addSpecification ContractDialog(&add);
        ContractDialog.exec();
        if (add.empty()) return;
        if (query.exec("INSERT INTO specificanion (Contract_number, Date_of_conclusion, Application_number) "
                       "VALUES ('"+add[1]+"', '"+ add[2]+ "', " + add[0] +")")) {
            ui->table_Spec->setRowCount(0);
            row = 0;
            query.exec("SELECT * FROM specificanion");
            while (query.next()) {
                 ui->table_Spec->insertRow(row);
                 ui->table_Spec->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
                 ui->table_Spec->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
                 ui->table_Spec->setItem(row, 2, new QTableWidgetItem(query.value(3).toString()));
                 ui->table_Spec->setItem(row, 3, new QTableWidgetItem(query.value(2).toString()));
                 row++;
            }
        } else QMessageBox::critical(this, "Внимание!","При попытке добавления произошла ошибка.\nУбедитесь, что форма заполнена правильно!");
    }
    else if (index == 2) {
        addBank BankDialog(&add, this);
        BankDialog.exec();
        if (add.empty()) return;
        if (query.exec("INSERT INTO Bank VALUES ('"+add[0]+"', '"+ add[1]+ "', '"+ add[2]+"')")) {
            ui->table_BIK->setRowCount(0);
            row = 0;
            query.exec("SELECT * FROM Bank");
            while (query.next()) {
                 ui->table_BIK->insertRow(row);
                 ui->table_BIK->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
                 ui->table_BIK->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
                 ui->table_BIK->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
                 row++;
            }
        } else QMessageBox::critical(this, "Внимание!","При попытке добавление произошла ошибка.\nУбедитесь, что форма заполнена правильно!");
    }
    else if (index == 3) {
        AddOKEI OKEIdialog(&add, this);
        OKEIdialog.exec();
        if (add.empty()) return;
        if (query.exec("INSERT INTO OKEI VALUES ('"+add[1]+"', "+ add[0]+ ", '"+ add[2]+"')")) {
            ui->table_OKEI->setRowCount(0);
            row = 0;
            query.exec("SELECT * FROM OKEI");
            while (query.next()) {
                 ui->table_OKEI->insertRow(row);
                 ui->table_OKEI->setItem(row, 1, new QTableWidgetItem(query.value(0).toString()));
                 ui->table_OKEI->setItem(row, 0, new QTableWidgetItem(query.value(1).toString()));
                 ui->table_OKEI->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
                 row++;
            }
        } else QMessageBox::critical(this, "Внимание!","При попытке добавление произошла ошибка.\nУбедитесь, что форма заполнена правильно!");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QSqlQuery query(db);
    int row;
    switch (ui->tabWidget->currentIndex()) {
    case 0: row = ui->table_Contracts->currentRow();
        if (row != -1) {
            if (query.exec("DELETE FROM Contracts WHERE Contract_number = '" + ui->table_Contracts->item(row,0)->text() + "'"))
                ui->table_Contracts->removeRow(row);
            else QMessageBox::critical(this, "Внимание!","При попытке удаления произошла ошибка.\nУбедитесь, что данная запись нигде не используется!");
        }
        break;
    case 1: row = ui->table_Spec->currentRow();
        if (row != -1) {
            if (query.exec("DELETE FROM specificanion WHERE Specifications = '" + ui->table_Spec->item(row,0)->text() + "'"))
                ui->table_Spec->removeRow(row);
            else QMessageBox::critical(this, "Внимание!","При попытке удаления произошла ошибка.\nУбедитесь, что данная запись нигде не используется!");
        }
        break;
    case 2: row = ui->table_BIK->currentRow();
        if (row != -1) {
            if (query.exec("DELETE FROM Bank WHERE BIK = '" + ui->table_BIK->item(row,0)->text() + "'"))
                ui->table_BIK->removeRow(row);
            else QMessageBox::critical(this, "Внимание!","При попытке удаления произошла ошибка.\nУбедитесь, что данная запись нигде не используется!");
        }
        break;
    case 3: row = ui->table_OKEI->currentRow();
        if (row != -1) {
            if (query.exec("DELETE FROM OKEI WHERE Code = " + ui->table_OKEI->item(row,0)->text()))
                ui->table_OKEI->removeRow(row);
            else QMessageBox::critical(this, "Внимание!","При попытке удаления произошла ошибка.\nУбедитесь, что данная запись нигде не используется!");
        }
        break;
    }
}


void MainWindow::on_updateRecord_clicked()
{
    QSqlQuery query(db);
    QStringList add;
    int row;
    int tab = ui->tabWidget->currentIndex();
    if (tab == 0) {
        row = ui->table_Contracts->currentRow();
        if (row == -1) return;
        for (int i = 0; i < 11; i++) add.push_back(ui->table_Contracts->item(row,i)->text());
        addContract ContractDialog(add, &add);
        ContractDialog.exec();
        if (add.empty()) return;
        if (query.exec("UPDATE Contracts SET Contract_number = '" + add[0] + "', Date_of_conclusion = '" + add[1] + "', Organization = '" + add[2] + "', Representative = '" + add[3] + "', Footing = '" + add[4] + "', Legal_address = '" + add[5] + "', OGRN = " + add[6] + ", INN = " + add[7] + ", KPP = " + add[8] + ", BIK = '" + add[9] + "', Pay_account = " + add[10] + " WHERE Contract_number = '" + ui->table_Contracts->item(row,0)->text() + "'")) {
            for (int i = 0; i < 11; i++) ui->table_Contracts->item(row,i)->setText(add[i]);
        } else QMessageBox::critical(this, "Внимание!","При попытке изменения произошла ошибка.\nУбедитесь, что не возникает конфликта ключей!");
    }
    else if (tab == 1) {
        row = ui->table_Spec->currentRow();
        if (row == -1) return;
        for (int i = 1; i < 4; i++) add.push_back(ui->table_Spec->item(row,i)->text());
        addSpecification ContractDialog(add, &add);
        ContractDialog.exec();
        if (add.empty()) return;
        if (query.exec("UPDATE specificanion SET Contract_number = '" + add[1] + "', Date_of_conclusion = '" + add[2] + "', Application_number = " + add[0] + " WHERE Specifications = '" + ui->table_Spec->item(row,0)->text() + "'")) {
            for (int i = 1; i < 4; i++) ui->table_Spec->item(row,i)->setText(add[i-1]);
        } else QMessageBox::critical(this, "Внимание!","При попытке изменения произошла ошибка.\nУбедитесь, что не возникает конфликта ключей!");
    }
    else if (tab == 2) {
        row = ui->table_BIK->currentRow();
        if (row == -1) return;
        for (int i = 0; i < 3; i++) add.push_back(ui->table_BIK->item(row,i)->text());
        addBank BankDialog(add, &add, this);
        BankDialog.exec();
        if (add.empty()) return;
        if (query.exec("UPDATE Bank SET BIK = '" + add[0] + "', Name = '" + add[1] + "', Corr_account = '" + add[2] + "' WHERE BIK = '" + ui->table_BIK->item(row,0)->text() + "'")) {
            ui->table_BIK->item(row,0)->setText(add[0]);
            ui->table_BIK->item(row,1)->setText(add[1]);
            ui->table_BIK->item(row,2)->setText(add[2]);
        } else QMessageBox::critical(this, "Внимание!","При попытке изменения произошла ошибка.\nУбедитесь, что не возникает конфликта ключей!");
    } else if (tab == 3) {
        row = ui->table_OKEI->currentRow();
        if (row == -1) return;
        for (int i = 0; i < 3; i++) add.push_back(ui->table_OKEI->item(row,i)->text());
        AddOKEI OKEIdialog(add, &add, this);
        OKEIdialog.exec();
        if (add.empty()) return;
        if (query.exec("UPDATE OKEI SET Code = " + add[0] + ", Name = '" + add[1] + "', ye = '" + add[2] + "' WHERE Code = " + ui->table_OKEI->item(row,0)->text())) {
            ui->table_OKEI->item(row,0)->setText(add[0]);
            ui->table_OKEI->item(row,1)->setText(add[1]);
            ui->table_OKEI->item(row,2)->setText(add[2]);
        } else QMessageBox::critical(this, "Внимание!","При попытке изменения произошла ошибка.\nУбедитесь, что не возникает конфликта ключей!");
    }
}


void MainWindow::on_addSpec_clicked()
{
    int row = ui->table_Contracts->currentRow();
    if (row == -1) return;
    QSqlQuery query(db);
    QStringList add;
    addSpecification ContractDialog(ui->table_Contracts->item(row, 0)->text(), &add);
    ContractDialog.exec();
    if (add.empty()) return;
    query.exec("INSERT INTO specificanion (Contract_number, Date_of_conclusion, Application_number) VALUES ('"+add[1]+"', '"+ add[2]+ "', " + add[0] +")");
}


void MainWindow::on_addGoods_clicked()
{
    int row = ui->table_Spec->currentRow();
    if (row == -1) return;
    QSqlQuery query(db);
    QStringList add;
    addGoods goods(&add,this);
    goods.exec();
    if (add.empty()) return;
    if (query.exec("INSERT INTO Goods (Name, Quantity, OKEI, Cost_per_unit, Date, Specifications) "
                   "VALUES ('"+add[0]+"', "+ add[1]+ ", "+ add[2].split(" ")[0] + ", "+ add[3] + ", CURRENT_DATE(), "+ ui->table_Spec->item(ui->table_Spec->currentRow(),0)->text() +")")) {
        ui->table_Goods->setRowCount(0);
        row = 0;
        query.exec("SELECT ID, Goods.Name, Quantity, OKEI.ye, Cost_per_unit FROM Goods, OKEI WHERE OKEI.Code = Goods.okei and Specifications = " + ui->table_Spec->item(ui->table_Spec->currentRow(),0)->text());
        while (query.next()) {
             ui->table_Goods->insertRow(row);
             for (int i = 0; i < 5; i++)
             ui->table_Goods->setItem(row, i, new QTableWidgetItem(query.value(i).toString()));
             row++;
        }
    } else QMessageBox::critical(this, "Внимание!","При попытке добавления произошла ошибка.\nУбедитесь, что форма заполнена правильно!");

}


void MainWindow::on_removeGoods_clicked()
{
    QSqlQuery query(db);
    int row = ui->table_Goods->currentRow();
    if (row == -1) return;
    if (query.exec("DELETE FROM Goods WHERE ID = " + ui->table_Goods->item(row,0)->text() + ""))
        ui->table_Goods->removeRow(row);
    else QMessageBox::critical(this, "Внимание!","При попытке удаления произошла ошибка.\nУбедитесь, что данная запись нигде не используется!");
}


void MainWindow::on_updateGoods_clicked()
{

    int row = ui->table_Goods->currentRow();
    if (row == -1) return;
    QSqlQuery query(db);
    QStringList add;
    for (int i = 1; i < 5; i++) add.push_back(ui->table_Goods->item(row,i)->text());
    addGoods ContractDialog(add, &add);
    ContractDialog.exec();
    if (add.empty()) return;
    if (query.exec("UPDATE Goods SET Name = '" + add[0] + "', Quantity = '" + add[1] + "', OKEI = " + add[2].split(" ")[1] + ", Cost_per_unit = " + add[3] + " WHERE Specifications = '" + ui->table_Goods->item(row,0)->text() + "'")) {
        for (int i = 1; i < 4; i++) ui->table_Goods->item(row,i)->setText(add[i-1]);
    } else QMessageBox::critical(this, "Внимание!","При попытке изменения произошла ошибка.\nУбедитесь, что не возникает конфликта ключей!");
}


void MainWindow::on_table_Spec_itemSelectionChanged()
{
    ui->table_Goods->setRowCount(0);
    if (ui->table_Spec->currentRow() == -1) return;
    int row = 0;
    QSqlQuery query(db);
    query.exec("SELECT ID, Goods.Name, Quantity, OKEI.ye, Cost_per_unit FROM Goods, OKEI WHERE OKEI.Code = Goods.okei and Specifications = " + ui->table_Spec->item(ui->table_Spec->currentRow(),0)->text());
    while (query.next()) {
         ui->table_Goods->insertRow(row);
         for (int i = 0; i < 5; i++)
         ui->table_Goods->setItem(row, i, new QTableWidgetItem(query.value(i).toString()));
         row++;
    }
    ui->table_Goods->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}


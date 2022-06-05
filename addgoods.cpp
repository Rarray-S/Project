#include "addgoods.h"
#include "ui_addgoods.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>

addGoods::addGoods(QStringList *res, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addGoods),
    result(res)
{
    ui->setupUi(this);
    QSqlQuery query(MainWindow::db);
    query.exec("select Code, ye from okei");
    while (query.next()) {
        ui->combo_ye->addItem(query.value(0).toString() + " " + query.value(1).toString());
    }
}

addGoods::addGoods(QStringList params, QStringList *res, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addGoods),
    result(res)
{
    ui->setupUi(this);
    ui->line_Name->setText(params[0]);
    ui->spin_Quan->setValue(params[1].toInt());
    ui->combo_ye->setCurrentText(params[2]);
    ui->double_Cost->setValue(params[3].toDouble());
    QSqlQuery query(MainWindow::db);
    query.exec("select Code, ye from okei");
    while (query.next()) {
        ui->combo_ye->addItem(query.value(0).toString() + " " + query.value(1).toString());
    }
}

addGoods::~addGoods()
{
    delete ui;
}

void addGoods::on_push_Ok_clicked()
{
    if (ui->line_Name->text() == "")
        QMessageBox::warning(this, "Внимание","Не все поля заполнены.");
    else accept();
}


void addGoods::on_push_Cancel_clicked()
{
    reject();
}


void addGoods::on_addGoods_accepted()
{
    result->clear();
    result->push_back(ui->line_Name->text());
    result->push_back(ui->spin_Quan->text());
    result->push_back(ui->combo_ye->currentText());
    result->push_back(ui->double_Cost->text().replace(",", "."));
}


void addGoods::on_addGoods_rejected()
{
    result->clear();
}


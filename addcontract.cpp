#include "addcontract.h"
#include "ui_addcontract.h"
#include "mainwindow.h"
#include <QIntValidator>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QDate>
#include <QSqlQuery>

addContract::addContract(QStringList *res, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addContract),
    result(res)
{
    ui->setupUi(this);
    ui->line_OGRN->setValidator(new QRegExpValidator(QRegExp("[0-9]{13}")));
    ui->line_KPP->setValidator(new QRegExpValidator(QRegExp("[0-9]{9}")));
    ui->line_INN->setValidator(new QRegExpValidator(QRegExp("[0-9]{9}")));
    ui->dateEdit->setDate(QDate::currentDate());
    QSqlQuery query(MainWindow::db);
    query.exec("SELECT * FROM Bank");
    while (query.next()) {
        ui->combo_BIK->addItem(query.value(0).toString() + " " + query.value(1).toString());
    }
}

addContract::addContract(QStringList params, QStringList *res, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addContract),
    result(res)
{
    ui->setupUi(this);
    ui->line_OGRN->setValidator(new QIntValidator());
    ui->line_KPP->setValidator(new QIntValidator());
    ui->line_INN->setValidator(new QIntValidator());
    QSqlQuery query(MainWindow::db);
    query.exec("SELECT * FROM Bank");
    while (query.next()) {
        ui->combo_BIK->addItem(query.value(0).toString() + " " + query.value(1).toString());
    }
    ui->line_Number->setText(params[0]);
    ui->dateEdit->setDate(QDate::fromString(params[1], "yyyy-MM-dd"));
    ui->line_Org->setText(params[2]);
    ui->line_Rep->setText(params[3]);
    ui->line_Foot->setText(params[4]);
    ui->line_LAddr->setText(params[5]);
    ui->line_OGRN->setText(params[6]);
    ui->line_INN->setText(params[7]);
    ui->line_KPP->setText(params[8]);
    ui->combo_BIK->setCurrentText(params[9]);
    ui->line_Pay->setText(params[10]);
}

addContract::~addContract()
{
    delete ui;
}

void addContract::on_addContract_accepted()
{
    result->clear();
    result->push_back(ui->line_Number->text());
    result->push_back(ui->dateEdit->date().toString("yyyy-MM-dd"));
    result->push_back(ui->line_Org->text());
    result->push_back(ui->line_Rep->text());
    result->push_back(ui->line_Foot->text());
    result->push_back(ui->line_LAddr->text());
    result->push_back(ui->line_OGRN->text());
    result->push_back(ui->line_INN->text());
    result->push_back(ui->line_KPP->text());
    result->push_back(ui->combo_BIK->currentText().split(" ")[0]);
    result->push_back(ui->line_Pay->text());
}


void addContract::on_addContract_rejected()
{
    result->clear();
}


void addContract::on_push_Ok_clicked()
{
    if (ui->line_Foot->text() == "" || ui->line_INN->text() == "" || ui->line_LAddr->text() == "" || ui->line_Number->text() == "" || ui->line_OGRN->text() == "" || ui->line_Org->text() == "" || ui->line_Rep->text() == "" || ui->line_KPP->text() == "" || ui->line_Pay->text() == "" || ui->combo_BIK->currentText() == "")
        QMessageBox::warning(this, "Внимание","Не все поля заполнены.");
    else accept();
}


void addContract::on_push_Cancel_clicked()
{
    reject();
}


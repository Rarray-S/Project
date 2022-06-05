#include "addspecification.h"
#include "ui_addspecification.h"
#include "mainwindow.h"
#include <QDate>
#include <QSqlQuery>

addSpecification::addSpecification(QStringList *res, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSpecification),
    result(res)
{
    ui->setupUi(this);
    QSqlQuery query(MainWindow::db);
    query.exec("SELECT Contract_number FROM Contracts");
    while (query.next()) {
        ui->combo_Contract->addItem(query.value(0).toString());
    }
    ui->dateEdit->setDate(QDate::currentDate());
}

addSpecification::addSpecification(QString CNumber, QStringList *res, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSpecification),
    result(res)
{
    ui->setupUi(this);
    ui->combo_Contract->setCurrentText(CNumber);
    ui->combo_Contract->setEnabled(false);
    ui->dateEdit->setDate(QDate::currentDate());
}

addSpecification::addSpecification(QStringList params, QStringList *res, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSpecification),
    result(res)
{
    ui->setupUi(this);
    ui->spin_App->setValue(params[0].toInt());
    ui->combo_Contract->setCurrentText(params[1]);
    ui->dateEdit->setDate(QDate::fromString(params[2], "yyyy-MM-dd"));
    QSqlQuery query(MainWindow::db);
    query.exec("SELECT Contract_number FROM Contracts");
    while (query.next()) {
        ui->combo_Contract->addItem(query.value(0).toString());
    }
}

addSpecification::~addSpecification()
{
    delete ui;
}

void addSpecification::on_push_Ok_clicked()
{
    accept();
}


void addSpecification::on_push_Cancel_clicked()
{
    reject();
}


void addSpecification::on_addSpecification_accepted()
{
    result->clear();
    result->push_back(ui->spin_App->text());
    result->push_back(ui->combo_Contract->currentText());
    result->push_back(ui->dateEdit->date().toString("yyyy-MM-dd"));
}


void addSpecification::on_addSpecification_rejected()
{
    result->clear();
}


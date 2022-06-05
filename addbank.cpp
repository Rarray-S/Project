#include "addbank.h"
#include "ui_addbank.h"
#include <QIntValidator>
#include <QRegExpValidator>
#include <QMessageBox>

addBank::addBank(QStringList *res, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBank),
    result(res)
{
    ui->setupUi(this);
    ui->line_BIK->setValidator(new QRegExpValidator(QRegExp("[0-9]{9}")));
    ui->line_Corr->setValidator(new QRegExpValidator(QRegExp("[0-9]{20}")));
}

addBank::addBank(QStringList params, QStringList *res, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBank),
    result(res)
{
    ui->setupUi(this);
    ui->line_BIK->setValidator(new QIntValidator);
    ui->line_Corr->setValidator(new QIntValidator);
    ui->line_BIK->setText(params[0]);
    ui->line_Name->setText(params[1]);
    ui->line_Corr->setText(params[2]);
}

addBank::~addBank()
{
    delete ui;
}

void addBank::on_push_Ok_clicked()
{
    if (ui->line_BIK->text() == "" || ui->line_Name->text() == "")
        QMessageBox::warning(this, "Внимание","Не все поля заполнены.");
    else accept();
}


void addBank::on_push_Cancel_clicked()
{
    reject();
}


void addBank::on_addBank_accepted()
{
    result->clear();
    result->push_back(ui->line_BIK->text());
    result->push_back(ui->line_Name->text());
    result->push_back(ui->line_Corr->text());
}


void addBank::on_addBank_rejected()
{
    result->clear();
}


#include "addokei.h"
#include "ui_addokei.h"
#include "QIntValidator"
#include <QMessageBox>

AddOKEI::AddOKEI(QStringList *res, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOKEI),
    result(res)
{
    ui->setupUi(this);
    ui->line_Code->setValidator(new QIntValidator());
}

AddOKEI::AddOKEI(QStringList params, QStringList *res, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOKEI),
    result(res)
{
    ui->setupUi(this);
    ui->line_Code->setValidator(new QIntValidator());
    ui->line_Code->setText(params[0]);
    ui->line_Name->setText(params[1]);
    ui->line_YE->setText(params[2]);
}

AddOKEI::~AddOKEI()
{
    delete ui;
}

void AddOKEI::on_AddOKEI_accepted()
{
    result->clear();
    result->push_back(ui->line_Code->text());
    result->push_back(ui->line_Name->text());
    result->push_back(ui->line_YE->text());
}


void AddOKEI::on_AddOKEI_rejected()
{
    result->clear();
}

void AddOKEI::on_push_Ok_clicked()
{
    if (ui->line_Code->text() == "" || ui->line_Name->text() == "" || ui->line_YE->text() == "")
        QMessageBox::warning(this, "Внимание","Не все поля заполнены.");
    else accept();
}


void AddOKEI::on_push_Cancel_clicked()
{
    reject();
}


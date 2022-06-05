#ifndef ADDCONTRACT_H
#define ADDCONTRACT_H

#include <QDialog>

namespace Ui {
class addContract;
}

class addContract : public QDialog
{
    Q_OBJECT

public:
    explicit addContract(QStringList *res, QWidget *parent = nullptr);
    explicit addContract(QStringList params, QStringList *res, QWidget *parent = nullptr);
    ~addContract();

private slots:
    void on_addContract_accepted();

    void on_addContract_rejected();

    void on_push_Ok_clicked();

    void on_push_Cancel_clicked();

private:
    Ui::addContract *ui;
    QStringList *result;
};

#endif // ADDCONTRACT_H

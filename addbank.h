#ifndef ADDBANK_H
#define ADDBANK_H

#include <QDialog>

namespace Ui {
class addBank;
}

class addBank : public QDialog
{
    Q_OBJECT

public:
    explicit addBank(QStringList *res, QWidget *parent = nullptr);
    explicit addBank(QStringList params, QStringList *res, QWidget *parent = nullptr);
    ~addBank();

private slots:
    void on_push_Ok_clicked();

    void on_push_Cancel_clicked();

    void on_addBank_accepted();

    void on_addBank_rejected();

private:
    Ui::addBank *ui;
    QStringList *result;
};

#endif // ADDBANK_H

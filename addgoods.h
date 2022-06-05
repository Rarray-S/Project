#ifndef ADDGOODS_H
#define ADDGOODS_H

#include <QDialog>

namespace Ui {
class addGoods;
}

class addGoods : public QDialog
{
    Q_OBJECT

public:
    explicit addGoods(QStringList *res, QWidget *parent = nullptr);
    explicit addGoods(QStringList params, QStringList *res, QWidget *parent = nullptr);
    ~addGoods();

private slots:
    void on_push_Ok_clicked();

    void on_push_Cancel_clicked();

    void on_addGoods_accepted();

    void on_addGoods_rejected();

private:
    Ui::addGoods *ui;
    QStringList *result;
};

#endif // ADDGOODS_H

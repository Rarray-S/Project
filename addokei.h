#ifndef ADDOKEI_H
#define ADDOKEI_H

#include <QDialog>
#include <QStringList>
namespace Ui {
class AddOKEI;
}

class AddOKEI : public QDialog
{
    Q_OBJECT

public:
    explicit AddOKEI(QStringList *res, QWidget *parent = nullptr);
    explicit AddOKEI(QStringList params, QStringList *res, QWidget *parent = nullptr);
    ~AddOKEI();

private slots:
    void on_AddOKEI_accepted();

    void on_AddOKEI_rejected();

    void on_push_Ok_clicked();

    void on_push_Cancel_clicked();

private:
    Ui::AddOKEI *ui;
    QStringList *result;
};

#endif // ADDOKEI_H

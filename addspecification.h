#ifndef ADDSPECIFICATION_H
#define ADDSPECIFICATION_H

#include <QDialog>

namespace Ui {
class addSpecification;
}

class addSpecification : public QDialog
{
    Q_OBJECT

public:
    explicit addSpecification(QStringList *res, QWidget *parent = nullptr);
    explicit addSpecification(QString CNumber, QStringList *res, QWidget *parent = nullptr);
    explicit addSpecification(QStringList params, QStringList *res, QWidget *parent = nullptr);
    ~addSpecification();

private slots:
    void on_push_Ok_clicked();

    void on_push_Cancel_clicked();

    void on_addSpecification_accepted();

    void on_addSpecification_rejected();

private:
    Ui::addSpecification *ui;
    QStringList *result;
};

#endif // ADDSPECIFICATION_H

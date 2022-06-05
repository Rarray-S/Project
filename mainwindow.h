#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QSqlDatabase db;

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_addRecord_clicked();

    void on_pushButton_2_clicked();

    void on_updateRecord_clicked();

    void on_addSpec_clicked();

    void on_addGoods_clicked();

    void on_removeGoods_clicked();

    void on_updateGoods_clicked();

    void on_table_Spec_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    bool db_open;
};
#endif // MAINWINDOW_H

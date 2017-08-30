#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlrelationaltablemodel.h>
#include <QtSql/qsqldriver.h>
#include <QtSql/qsqltablemodel.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum Tab {PRODUCTS, ORDERS};
    QString getCurrentTable();
    void selectCurrentTable();
private slots:
    void on_pbnExecQuery_clicked();
    void on_pbnTruncateTable_clicked();
    void on_pbnChoosePath_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_queryExecuted(QString msg);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *productsModel;
    QSqlRelationalTableModel *ordersModel;
};

#endif // MAINWINDOW_H

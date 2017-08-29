#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/qsqldatabase.h>
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

private slots:
    void on_pbnExecQuery_clicked();
    void on_pbnTruncateTable_clicked();

    void on_pbnChoosePath_clicked();

private:
    Ui::MainWindow *ui;
    void connectToDb();
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // MAINWINDOW_H

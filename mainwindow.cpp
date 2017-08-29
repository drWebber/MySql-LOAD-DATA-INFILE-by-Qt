#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include <qdebug.h>
#include <qfiledialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectToDb();
    QSqlQuery("SET NAMES 'cp1251'").exec();
    model = new QSqlTableModel(this);
    model->setTable("main");
    model->select();

    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL3");
    db.setHostName("localhost");
    db.setDatabaseName("bigdata");
    db.setUserName("root");

    if (!db.open()) {
        qDebug() << "Соединение с БД не установлено!";
    }
}

void MainWindow::on_pbnExecQuery_clicked()
{
    QSqlQuery query("LOAD DATA INFILE '" + ui->lineEdit->text() + "' INTO TABLE `main`");
    model->select();
}

void MainWindow::on_pbnTruncateTable_clicked()
{
    QSqlQuery("TRUNCATE TABLE `main`").exec();
    model->select();
}

void MainWindow::on_pbnChoosePath_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open file"),
                                              "/home", tr("Text (*.txt)"));
    if (!path.isEmpty()) {
        ui->lineEdit->setText(path);
    }
}

#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include <QTime>
#include <qdebug.h>
#include <qfiledialog.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dataimport.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit->setPlaceholderText("The path of import file");
    currentTable = ui->tabWidget->currentIndex();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL3");
    db.setHostName("localhost");
    db.setDatabaseName("bigdata");
    db.setUserName("root");

    if (!db.open()) {
        qDebug() << "Failed to connect!";
    }

    QSqlQuery("SET NAMES 'UTF8'").exec();
    QSqlQuery("SET foreign_key_checks = 0").exec();

    products = new Products(ui->tbvProducts);
    tables.append(products);

    ui->lbQueryMsg->setVisible(false);

    ordersModel = new QSqlRelationalTableModel(this);
    ordersModel->setTable("orders");
    ordersModel->setRelation(0, QSqlRelation("products", "id", "article"));
    ordersModel->select();

    ui->tbvOrders->setModel(ordersModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getCurrentTable()
{
    switch (currentTable) {
    case Tab::PRODUCTS: return "products";
    case Tab::ORDERS: return "orders";
    }
    return QString();
}

void MainWindow::selectCurrentTable()
{
    switch (ui->tabWidget->currentIndex()) {
    case Tab::PRODUCTS:
//        productsModel->select();
        break;
    case Tab::ORDERS:
        ordersModel->select();
    }
}

void MainWindow::on_pbnExecQuery_clicked()
{
    qDebug() << "on_pbnExecQuery_clicked" << currentTable;
    tables.at(currentTable)->setImportFilePath(ui->lineEdit->text());
    tables.at(currentTable)->start();
    tables.at(currentTable)->select();
}

void MainWindow::on_pbnTruncateTable_clicked()
{
    QSqlQuery("TRUNCATE TABLE `" + getCurrentTable() + "`").exec();
    selectCurrentTable();
}

void MainWindow::on_pbnChoosePath_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open file"),
                                              "/home", tr("Text (*.txt)"));
    if (!path.isEmpty()) {
        ui->lineEdit->setText(path);
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);
    currentTable = ui->tabWidget->currentIndex();
    qDebug() << Tab(currentTable);
    ui->lbQueryMsg->setVisible(false);
}

void MainWindow::on_queryExecuted(QString msg)
{
    ui->lbQueryMsg->setVisible(true);
    if (msg.contains("Elapsed")) {
        ui->lbQueryMsg->setStyleSheet("background-color: #5CCD5C; "
                                      "padding: 5px; color: #FFF");
    } else {
        ui->lbQueryMsg->setStyleSheet("background-color: #CD5C5C; "
                                      "padding: 5px; color: #FFF");
    }
    ui->lbQueryMsg->setText(msg);
}

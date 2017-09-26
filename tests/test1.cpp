#include "test1.h"
#include "ui_test1.h"
#include <qdatetime.h>
#include <qsqlquery.h>
#include <qdebug.h>
#include <qsqlerror.h>

Test1::Test1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Test1)
{
    ui->setupUi(this);
    QSqlQuery q;
    q.exec("SELECT `article` FROM `products`");
    while (q.next()) {
        articles.append(q.value(0).toString());
    }
//    rowsToInsert = articles.count()/3;
    rowsToInsert = articles.count();
    qDebug() << "rows count:" << articles.count();
}

Test1::~Test1()
{
    delete ui;
}

void Test1::on_pbnTest1_clicked()
{
    qDebug() << QDateTime::currentDateTime().toString() << "test 1 started";
    QSqlQuery query;
    query.exec("START TRANSACTION");
    query.exec("DELETE FROM `store` WHERE 1");
    for (int i = 0; i < rowsToInsert; ++i) {
        query.prepare("INSERT INTO `store` VALUES("
                      "(SELECT `id` FROM `products` WHERE `article` = :article), "
                      "" + QString::number(i) + ")");
        query.bindValue(":article", articles.at(i));
        query.exec();
    }
    query.exec("COMMIT");
    qDebug() << QDateTime::currentDateTime().toString() << "test 1 finished";
}

void Test1::on_pbnTest2_clicked()
{
    qDebug() << QDateTime::currentDateTime().toString() << "test 2 started";
    QSqlQuery query;
    query.exec("START TRANSACTION");
    query.exec("DELETE FROM `store` WHERE 1");
    QString inPredicate;
    for (int i = 0; i < rowsToInsert; ++i) {
        inPredicate.append("\"" + articles.at(i) + "\", ");
    }
    inPredicate.chop(2);

    QStringList ids;
    query.exec("SELECT `id` FROM `products` WHERE `article` IN(" + inPredicate + ")");
    while (query.next()) {
        ids.append(query.value(0).toString());
    }
    if (ids.count() >= rowsToInsert) {
        for (int i = 0; i < rowsToInsert; ++i) {
            query.prepare("INSERT INTO `store` VALUES(:id, :count)");
            query.bindValue(":id", ids.at(i));
            query.bindValue(":count", QString::number(i));
            query.exec();
        }
    }
    query.exec("COMMIT");

    qDebug() << QDateTime::currentDateTime().toString() << "test 2 finished";
}

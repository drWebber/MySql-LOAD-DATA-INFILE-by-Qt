#include "products.h"
#include <qdatetime.h>
#include <qdebug.h>
#include <qsqlquery.h>
#include <qsqlerror.h>

Products::Products(QTableView *tableView) : Table(tableView)
{
    model = new QSqlTableModel();
    model->setTable("products");
    model->select();

    tableView->setModel(model);
}

void Products::setImportFilePath(const QString &value)
{
    importFilePath = value;
}

QString Products::getStatement()
{
    return "LOAD DATA INFILE '" + importFilePath
            + "' IGNORE INTO TABLE `orders`(@id, `date`, `count`)"
              "SET id = (SELECT `id` FROM `products` WHERE article = @id)";
}

void Products::run()
{
    QSqlDatabase conn = getConnection();
    QSqlQuery query = QSqlQuery(conn);

    QTime t;
    t.start();

    if (!query.exec(getStatement())) {
        qDebug() << "HERE" << query.lastError().text();
//        emit queryExecuted(query.lastError().text());
    } else {
        double elapsed = t.elapsed();
        qDebug() << "elapsed time:" << elapsed;
//        emit queryExecuted("Elapsed time:" +
//                           QString::number(elapsed/1000, 'f', 2) + "sec");
    }
    conn.close();
}

void Products::select()
{
    model->select();
}

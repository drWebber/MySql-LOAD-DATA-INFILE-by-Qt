#include "table.h"
#include <qsqlerror.h>
#include <qdebug.h>
#include <qdatetime.h>

Table::Table(QTableView *tableView, QObject *parent) : QThread(parent)
{
    this->tableView = tableView;
}

QString Table::getLastQuery() const
{
    return lastQuery;
}

QSqlDatabase Table::getConnection()
{
    QSqlDatabase conn = QSqlDatabase::addDatabase("QMYSQL3", QTime::currentTime().toString());
    conn.setHostName("localhost");
    conn.setDatabaseName("bigdata");
    conn.setUserName("root");

    if (!conn.open()) {
        qDebug() << "Failed to connect!";
        return QSqlDatabase();
    }
    return conn;
}

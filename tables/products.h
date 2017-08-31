#ifndef PRODUCTS_H
#define PRODUCTS_H

#include "tables/table.h"
#include <QtSql/qsqltablemodel.h>

class Products : public Table
{
public:
    Products(QTableView *tableView);
private:
    QSqlTableModel *model;
    QString importFilePath;
    QString getStatement();
public:
    void setImportFilePath(const QString &value);
protected:
    void run();

    // Table interface
public:
    void select();
};

#endif // PRODUCTS_H

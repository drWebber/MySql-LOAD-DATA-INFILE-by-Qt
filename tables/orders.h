#ifndef ORDERS_H
#define ORDERS_H

#include "tables/table.h"

class Orders : public Table
{
public:
    Orders(QTableView *tableView);

    // Table interface
public:
    QString getStatement(QString importFilePath);
};

#endif // ORDERS_H

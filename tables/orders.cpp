#include "orders.h"

Orders::Orders(QTableView *tableView) : Table(tableView)
{

}

QString Orders::getStatement(QString importFilePath)
{
    return "LOAD DATA INFILE '" + importFilePath
            + "' INTO TABLE `products`";
}

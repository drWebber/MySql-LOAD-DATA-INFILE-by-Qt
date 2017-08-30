#ifndef PRODUCTS_H
#define PRODUCTS_H

#include "tables/table.h"

class Products : public Table
{
public:
    Products();

    // Table interface
public:
    QString getStatement(QString importFilePath);
};

#endif // PRODUCTS_H

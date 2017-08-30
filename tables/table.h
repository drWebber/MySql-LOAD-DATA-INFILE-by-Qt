#ifndef TABLE_H
#define TABLE_H

#include <qstring.h>



class Table
{
public:
    Table();
    virtual QString getStatement(QString importFilePath) = 0;
    QString getLastQuery() const;
private:
    QString lastQuery;
};

#endif // TABLE_H

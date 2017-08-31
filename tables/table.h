#ifndef TABLE_H
#define TABLE_H

#include <qstring.h>
#include <qtableview.h>
#include <qthread.h>
#include <qsqldatabase.h>

class Table : public QThread
{
    Q_OBJECT
public:
    Table(QTableView *tableView, QObject *parent = 0);
    virtual QString getStatement() = 0;
    virtual void setImportFilePath(const QString &value) = 0;
    virtual void select() = 0;
    QString getLastQuery() const;
protected:
    QTableView *tableView;
    QSqlDatabase getConnection();
private:
    QString lastQuery;
};

#endif // TABLE_H

#include "dataimport.h"

#include <qsqlquery.h>
#include <qsqlerror.h>
#include <qdatetime.h>
#include <qdebug.h>

DataImport::DataImport(const QString &statement, QObject *parent)
    : QThread(parent)
{
    this->statement = statement;
}

void DataImport::run()
{
}

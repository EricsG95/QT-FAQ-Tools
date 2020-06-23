#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <string>
#include <vector>
#include <fstream>

#include <QString>
#include <QtSql>

#include "ibdhandler.h"

class DbHandler : public IDbHandler
{
public:
    DbHandler();
    QString dbConnect() override;
    void init(std::vector<QString>& dbparams ,int port) override;
    bool is_open() override {return database_.isOpen(); }
    QString lastError() override;
    void close() override;

private:
    QSqlDatabase database_;
    QString username_;
    QString password_;
    QString hostname_;
    QString dbname_;
    int port_;
};

#endif // DBHANDLER_H

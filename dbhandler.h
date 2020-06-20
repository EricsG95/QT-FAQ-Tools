#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <string>
#include <vector>
#include <fstream>

#include <QString>
#include <QtSql>

class DbHandler
{
public:
    DbHandler();
    DbHandler(std::vector<QString>& dbparams ,int port);

    bool is_open(){ return database_.isOpen(); }

    void setParams(
            QString username,
            QString password,
            QString hostname,
            QString dbname,
            int port);

    QString dbConnect();
    QString lastError();
    void close();

    std::vector<QString> table_names;

private:
    QString username_;
    QString password_;
    QString hostname_;
    QString dbname_;
    int port_;
    QSqlDatabase database_;
};

#endif // DBHANDLER_H

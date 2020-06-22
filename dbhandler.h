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
    QString dbConnect();
    bool is_open(){ return database_.isOpen(); }
    QString lastError();
    void close();

private:
    QSqlDatabase database_;
    QString username_;
    QString password_;
    QString hostname_;
    QString dbname_;
    int port_;
};

#endif // DBHANDLER_H

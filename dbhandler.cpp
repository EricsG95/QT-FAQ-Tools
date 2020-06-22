#include "dbhandler.h"

DbHandler::DbHandler(){
    database_.removeDatabase("qt_sql_default_connection");
    database_ = QSqlDatabase::addDatabase("QPSQL");
}

DbHandler::DbHandler(std::vector<QString>& dbparams ,int port)
{
    database_.removeDatabase("qt_sql_default_connection");
    database_ = QSqlDatabase::addDatabase("QPSQL");

    username_ = dbparams[0];
    password_ = dbparams[1];
    hostname_ = dbparams[2];
    dbname_ = dbparams[3];
    port_ = port;
}

QString DbHandler::dbConnect()
{
    if(database_.isOpen())
    {
        database_.close();
    }

    database_.setHostName(hostname_);
    database_.setDatabaseName(dbname_);
    database_.setPort(port_);

    database_.open(username_,password_);

    if(database_.isOpen())
        return QString("Database connected");
    else
        return database_.lastError().text();
}

void DbHandler::close()
{
    if(database_.isOpen())
    {
        database_.close();
    }
}

QString DbHandler::lastError()
{
    return database_.lastError().text();
}

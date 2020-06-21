#include "dbhandler.h"

DbHandler::DbHandler(){
    database_.removeDatabase("qt_sql_default_connection");
    database_ = QSqlDatabase::addDatabase("QPSQL");

    //username, password, dbname, hostname, port
    setParams("faqadmin",
               "222&autoDesk",
               "postgresql-10318-0.cloudclusters.net",
               "faqtooldb",
               10318);
}

DbHandler::DbHandler(std::vector<QString>& dbparams ,int port){
    username_ = dbparams[0];
    password_ = dbparams[1];
    hostname_ = dbparams[2];
    dbname_ = dbparams[3];
    port_ = port;

    database_.removeDatabase("qt_sql_default_connection");
    database_ = QSqlDatabase::addDatabase("QPSQL");

//    table_names = std::vector<QString>();
//    table_names.push_back("projects");
//    table_names.push_back("questions");
}

void DbHandler::setParams(QString username,
                          QString  password,
                          QString  hostname,
                          QString  dbname,
                          int port){
    username_ = username;
    hostname_ = hostname;
    password_ = password;
    dbname_ = dbname;
    port_ = port;
}

void DbHandler::close(){
    if(database_.isOpen())
    {
        database_.close();
    }
}

QString DbHandler::lastError(){
    return database_.lastError().text();
}

QString DbHandler::dbConnect(){
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

#include "settingsfileservice.h"

SettingsFileService::SettingsFileService(){}

void SettingsFileService::loadSettings(
        std::vector<QString>& dbparams, int& port)
{
    std::ifstream ifs;
    ifs.open("settings.ini");
    std::string name,pass,host,db;

    if(!ifs.is_open()){
        applyDefaultSettings(dbparams, port);
    } else {
        ifs >> name >> pass >> host >> db >> port;
        dbparams[0] = QString::fromStdString(name);
        dbparams[1] = QString::fromStdString(pass);
        dbparams[2] = QString::fromStdString(host);
        dbparams[3] = QString::fromStdString(db);
        ifs.close();
    }
}

void SettingsFileService::applyDefaultSettings(
        std::vector<QString>& dbparams, int& port)
{
    dbparams[0] = "faqadmin";
    dbparams[1] = "222&autoDesk";
    dbparams[2] = "postgresql-10318-0.cloudclusters.net";
    dbparams[3] = "faqtooldb";
    port = 10318;
}

void SettingsFileService::saveSettings(DbSettings& dialog)
{
    std::fstream ofs;
    ofs.open("settings.ini",std::ios::out);
    ofs << dialog.username().toStdString() << std::endl
        << dialog.password().toStdString() << std::endl
        << dialog.hostname().toStdString() << std::endl
        << dialog.dbname().toStdString() << std::endl
        << dialog.port();
    ofs.close();
}

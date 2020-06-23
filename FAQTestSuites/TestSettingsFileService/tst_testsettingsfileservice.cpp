#include <QtTest>
#include <QDialog>

#include "../../settingsfileservice.h"
#include "../../settingsfileservice.cpp"

#include <fstream>
#include <iostream>

class TestSettingsFileService : public QObject
{
    Q_OBJECT

private slots:
    void settingsLoadedSuccessfully();
    void newSettingsSavedSuccessfully();

private:
    SettingsFileService mSettingsFileService;
};

void TestSettingsFileService::settingsLoadedSuccessfully()
{
    std::vector<QString> empty_db_params(4,0);
    int empty_port_setting;

    // Read current settings
    std::ifstream ifs;
    ifs.open("settings.ini");

    std::string name,pass,host,db;
    int port;

    // No settings existed, hence will be defaulted
    if(!ifs.is_open()){
        mSettingsFileService.loadSettings(empty_db_params, empty_port_setting);

        QCOMPARE(empty_db_params[0], "faqadmin");
        QCOMPARE(empty_db_params[1], "222&autoDesk");
        QCOMPARE(empty_db_params[2], "postgresql-10318-0.cloudclusters.net");
        QCOMPARE(empty_db_params[3], "faqtooldb");
        QCOMPARE(empty_port_setting, 10318);
    } else {
        mSettingsFileService.loadSettings(empty_db_params, empty_port_setting);

        ifs >> name >> pass >> host >> db >> port;

        QCOMPARE(empty_db_params[0], QString::fromStdString(name));
        QCOMPARE(empty_db_params[1], QString::fromStdString(pass));
        QCOMPARE(empty_db_params[2], QString::fromStdString(host));
        QCOMPARE(empty_db_params[3], QString::fromStdString(db));
        QCOMPARE(empty_port_setting, port);

        ifs.close();
    }
}

void TestSettingsFileService::newSettingsSavedSuccessfully()
{
    std::vector<QString> new_db_params(4,0);
    int new_port;

    new_db_params[0] = "newAdmin";
    new_db_params[1] = "newPass";
    new_db_params[2] = "newHost";
    new_db_params[3] = "newDb";
    new_port = 11222;

    mSettingsFileService.saveSettings(new_db_params, new_port);

    std::ifstream ifs;
    ifs.open("settings.ini");

    std::string name,pass,host,db;
    int port;

    if(ifs.is_open()){
        ifs >> name >> pass >> host >> db >> port;

        QCOMPARE(name, "newAdmin");
        QCOMPARE(pass, "newPass");
        QCOMPARE(host, "newHost");
        QCOMPARE(db, "newDb");
        QCOMPARE(port, 11222);

        ifs.close();
    }

}

QTEST_APPLESS_MAIN(TestSettingsFileService)

#include "tst_testsettingsfileservice.moc"

#include <QtTest>

#include "../../dbsettings.h"
#include "../../dbsettings.cpp"

#include "../../settingsfileservice.h"
#include "../../settingsfileservice.cpp"

class TestSettingsFileService : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void loadSettingsSuccessfully();

private:
    SettingsFileService mSettingsFileService;
};

void TestSettingsFileService::initTestCase()
{

}

void TestSettingsFileService::loadSettingsSuccessfully()
{
    std::vector<QString> db_settings(4,0);
    int port_setting;

    mSettingsFileService.loadSettings(db_settings, port_setting);

    QCOMPARE(db_settings[0], "faqadmin");
    QCOMPARE(db_settings[1], "222&autoDesk");
    QCOMPARE(db_settings[2], "postgresql-10318-0.cloudclusters.net");
    QCOMPARE(db_settings[3], "faqtooldb");
    QCOMPARE(port_setting, 10318);
}

QTEST_APPLESS_MAIN(TestSettingsFileService)

#include "tst_testsettingsfileservice.moc"

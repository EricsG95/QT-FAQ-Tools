#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <QMainWindow>

#include <fstream>
#include <iostream>

#include "dbsettings.h"

class SettingsFileService
{
public:
    SettingsFileService();
    void loadSettings(std::vector<QString>& dbparams, int& port);
    void applyDefaultSettings(std::vector<QString>& dbparams, int& port);
    void saveSettings(DbSettings& dialog);
};

#endif // FILESERVICE_H

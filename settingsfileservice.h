#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <QMainWindow>

#include <fstream>
#include <iostream>

#include "isettingsfileservice.h"

class SettingsFileService : public ISettingsFileService
{
public:
    SettingsFileService();
    void loadSettings(std::vector<QString>& dbparams, int& port) override;
    void saveSettings(std::vector<QString>& dbparams, int& port) override;

private:
    void applyDefaultSettings(std::vector<QString>& dbparams, int& port) override;
};

#endif // FILESERVICE_H

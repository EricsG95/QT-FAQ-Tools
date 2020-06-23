#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <QMainWindow>

#include <fstream>
#include <iostream>

class SettingsFileService
{
public:
    SettingsFileService();
    void loadSettings(std::vector<QString>& dbparams, int& port);
    void saveSettings(std::vector<QString>& dbparams, int& port);

private:
    void applyDefaultSettings(std::vector<QString>& dbparams, int& port);
};

#endif // FILESERVICE_H

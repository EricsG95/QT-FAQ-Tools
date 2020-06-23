#ifndef ISETTINGSFILESERVICE_H
#define ISETTINGSFILESERVICE_H

#include <QMainWindow>

class ISettingsFileService
{
public:
    virtual ~ISettingsFileService() noexcept = default;
    virtual void loadSettings(std::vector<QString>& dbparams, int& port) = 0;
    virtual void saveSettings(std::vector<QString>& dbparams, int& port) = 0;
    virtual void applyDefaultSettings(std::vector<QString>& dbparams, int& port) = 0;
};

#endif // ISETTINGSFILESERVICE_H

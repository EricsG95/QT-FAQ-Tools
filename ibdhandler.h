#ifndef IDBHANDLER_H
#define IDBHANDLER_H

#include <string>
#include <vector>
#include <fstream>

#include <QString>
#include <QtSql>

class IDbHandler
{
public:
    virtual ~IDbHandler() noexcept = default;
    virtual QString dbConnect() = 0;
    virtual void init(std::vector<QString>& dbparams ,int port) = 0;
    virtual bool is_open() = 0;
    virtual QString lastError() = 0;
    virtual void close() = 0;
};

#endif // IDBHANDLER_H

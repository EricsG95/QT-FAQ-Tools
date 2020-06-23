#include "mainwindow.h"
#include "di.h"
#include "settingsfileservice.h"

//#include "dbhandler.h"
//#include "IDbHandler.h"

#include <QApplication>

namespace di = boost::di;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     auto injector = di::make_injector(
       di::bind<SettingsFileService>.to<SettingsFileService>(),
       di::bind<IDbHandler>.to<DbHandler>()
     );

    std::unique_ptr<MainWindow> w =
            injector.create<std::unique_ptr<MainWindow>>();

    w->show();

    return a.exec();
}

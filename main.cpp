#include "mainwindow.h"
#include "di.h"

#include <QApplication>

namespace di = boost::di;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     auto injector = di::make_injector(
       di::bind<ISettingsFileService>.to<SettingsFileService>(),
       di::bind<IDbHandler>.to<DbHandler>()
     );

    std::unique_ptr<MainWindow> w =
            injector.create<std::unique_ptr<MainWindow>>();

    w->show();

    return a.exec();
}

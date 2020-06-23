# Qt C++ Learning Journal
FAQ tools created with Qt and C++. This project is created to facilitate my learning in understanding C++ and using it in the real-life project. 

# FAQ Tool
This FAQ project was inspired where my team needed a tool to document down all FAQs of different projects, hence we did not need to reply to the same queries through email again and again. This will then make available to our clients who used our services.

# Application Features
Features wise, I am keeping it simple, but more on the focus to understand the nature of C++ and how it is different from a higher abstraction language such as C#, as well as JavaScript.

# Learning Objectives
Here in this project, my objective was first:

1. To be able to achieve application features in using C++
   - Such as connecting to a database
   - Execute query on a database
   - Load data to view
   - Simple data filtering

   ![FAQ Tool SS](https://i.ibb.co/3Rg1yk5/project-faq.jpg)

2. Understanding the nature of C++ and how it is differing to other languages in terms of data types, pointers, STL and exploring further to more in-depth topics

3. Applying common best practices
   - Dependency injection using [Boost DI](https://github.com/boost-experimental/di)
   
      ```
      main.cpp

      auto injector = di::make_injector(
         di::bind<ISettingsFileService>.to<SettingsFileService>(),
         di::bind<IDbHandler>.to<DbHandler>()
      );

      std::unique_ptr<MainWindow> w =
         injector.create<std::unique_ptr<MainWindow>>();
      ```

      ```
      mainwindow.cpp

      MainWindow::MainWindow(std::shared_ptr<ISettingsFileService> fileService,
                        std::shared_ptr<IDbHandler> dbHandler)
      : QMainWindow(nullptr)
      , fileService_(fileService)
      , db_handler_(dbHandler)
      , ui(new Ui::MainWindow) {...}
      ```

   - Unit testing using [Qt Test](https://doc.qt.io/qt-5/qtest-overview.html)

      >********* Start testing of TestSettingsFileService *********\
      >Config: Using QtTest library 5.15.0, Qt 5.15.0 (x86_64-little_endian-llp64 shared (dynamic) release build; by GCC 8.1.0)\
      PASS   : TestSettingsFileService::initTestCase()\
      PASS   : TestSettingsFileService::settingsLoadedSuccessfully()\
      PASS   : TestSettingsFileService::newSettingsSavedSuccessfully()\
      PASS   : TestSettingsFileService::cleanupTestCase()\
      Totals: 4 passed, 0 failed, 0 skipped, 0 blacklisted, 1ms\
      >********* Finished testing of TestSettingsFileService *********

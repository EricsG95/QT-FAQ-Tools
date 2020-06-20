#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dbhandler.h"

#include <QMainWindow>
#include <QMessageBox>
#include <fstream>
#include <iostream>

#include <memory>

#include "dbsettings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSettings_triggered();

private:
    std::unique_ptr<DbHandler> db_instance_;
    Ui::MainWindow *ui;

    bool initialiseDB();
    void loadNewDatabase();
    bool loadSettings(std::vector<QString>& dbparams, int& port);
};
#endif // MAINWINDOW_H

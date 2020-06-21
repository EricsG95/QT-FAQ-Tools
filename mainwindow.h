#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <fstream>
#include <iostream>
#include <memory>

#include "dbsettings.h"
#include "dbhandler.h"
#include "dataobject.h"

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
    void onTvFaqsItemClicked(QTreeWidgetItem *item, int column);
    void on_btn_reset_clicked();
    void on_btn_filter_clicked();

    void on_actionExit_triggered();

    void on_actionReconnect_triggered();

private:
    std::unique_ptr<DbHandler> db_instance_;
    std::unique_ptr<DataObject> faq_data_;
    Ui::MainWindow *ui;

    void initialiseDB();
    void loadDatabase();
    void loadSettings(std::vector<QString>& dbparams, int& port);

    bool prepareViewData();
    void initialiseTreeView();

    // Could be moved to db handler
    void excuteQueryOnDb(QString command);
    void loadDataToFaqTreeView();
};
#endif // MAINWINDOW_H

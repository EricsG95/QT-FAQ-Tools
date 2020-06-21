#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadDatabase();
}

void MainWindow::loadDatabase()
{
    if(db_instance_ != nullptr)
    {
        db_instance_->close();
        db_instance_ = nullptr;
    }

    initialiseDB();

    ui->statusbar->showMessage(db_instance_->dbConnect());
}

void MainWindow::initialiseDB(){
    int port_setting;
    std::vector<QString> db_settings(4,0);

    loadSettings(db_settings,port_setting);

    db_instance_ = std::make_unique<DbHandler>(
                db_settings, port_setting);
}

// Loading settings
void MainWindow::loadSettings(std::vector<QString>& dbparams,
                              int& port)
{
    std::ifstream ifs;
    ifs.open("settings.ini");
    std::string name,pass,host,db;

    if(!ifs.is_open()){
        dbparams[0] = "faqadmin";
        dbparams[1] = "222&autoDesk";
        dbparams[2] = "postgresql-10318-0.cloudclusters.net";
        dbparams[3] = "faqtooldb";
        port = 10318;
    } else {
        ifs >> name >>  pass >>  host >> db >> port;
        dbparams[0] = QString::fromStdString(name);
        dbparams[1] = QString::fromStdString(pass);
        dbparams[2] = QString::fromStdString(host);
        dbparams[3] = QString::fromStdString(db);
        ifs.close();
    }
}

void MainWindow::on_actionSettings_triggered()
{
    // Runs a dialog to update the DB settings
    DbSettings dialog(this);
    dialog.exec();

    if(dialog.result() != QDialog::DialogCode::Accepted)
    {
        ui->statusbar->showMessage("Settings not updated");
        return;
    }

    // Writes it to 'settings.ini' file
    std::fstream ofs;
    ofs.open("settings.ini",std::ios::out);
    ofs << dialog.username().toStdString() << std::endl << dialog.password().toStdString()
        << std::endl << dialog.hostname().toStdString() << std::endl << dialog.dbname().toStdString()
        << std::endl << dialog.port();

    ofs.close();
    loadDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

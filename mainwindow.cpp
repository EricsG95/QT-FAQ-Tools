#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadNewDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::initialiseDB(){
    int port_setting = 10318;
    std::vector<QString> db_settings(4,0);
    bool ok_state = loadSettings(db_settings,port_setting);

    if(ok_state)
    {
        // Make a DB handler
        db_instance_ = std::make_unique<DbHandler>(
                    db_settings, port_setting);
    }
    return ok_state;
}

// Loading settings
bool MainWindow::loadSettings(std::vector<QString>& dbparams,
                              int& port)
{
    // load connection settings from 'settings.ini'
    dbparams[0] = "faqadmin";
    dbparams[1] = "222&autoDesk";
    dbparams[2] = "postgresql-10318-0.cloudclusters.net";
    dbparams[3] = "faqtooldb";
    port = 10318;

    std::ifstream ifs;
    ifs.open("settings.ini");
    std::string name,pass,host,db;

    if(!ifs.is_open())
    {
        return false;
    }
    else
    {
        ifs >> name >>  pass >>  host >> db >> port;
    }

    dbparams[0] = QString::fromStdString(name);
    dbparams[1] = QString::fromStdString(pass);
    dbparams[2] = QString::fromStdString(host);
    dbparams[3] = QString::fromStdString(db);

    ifs.close();

    return true;
}

// Loading new database
void MainWindow::loadNewDatabase()
{
    // Clear previous DB Handler, dead connection
    if(db_instance_ != nullptr)
    {
        db_instance_->close();
        db_instance_ = nullptr;
    }

    bool ok_state = initialiseDB();
    if(!ok_state)
    {
        QMessageBox msg;
        msg.setText("Settings not loaded correctly.");
        msg.exec();
        return;
    }

    // Connect to the DB
    ui->statusbar->showMessage(db_instance_->dbConnect());
}

void MainWindow::on_actionSettings_triggered()
{
    // Runs a dialog to update the DB settings
    DbSettings dialog(this);
    dialog.exec();

    if(dialog.result() != QDialog::DialogCode::Accepted)
    {
        ui->statusbar->showMessage("Settings not set. No data updated.");
        return;
    }

    // Writes it to 'settings.ini' file
    std::fstream ofs;
    ofs.open("settings.ini",std::ios::out);
    ofs << dialog.username().toStdString() << std::endl << dialog.password().toStdString()
        << std::endl << dialog.hostname().toStdString() << std::endl << dialog.dbname().toStdString()
        << std::endl << dialog.port();

    ofs.close();
    ui->statusbar->showMessage("Database connected");
}

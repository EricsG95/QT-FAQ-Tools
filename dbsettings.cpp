#include "dbsettings.h"
#include "ui_dbsettings.h"

DbSettings::DbSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DbSettings)
{
    ui->setupUi(this);

    std::string name,pass,host,db;
    int port;

    std::ifstream ifs;
    ifs.open("settings.ini");

    if(ifs.is_open())
    {
        ifs >> name >>  pass >>  host >> db >> port;
        ifs.close();
        ui->le_username->setText(QString::fromStdString(name));
        ui->le_password->setText(QString::fromStdString(pass));
        ui->le_host->setText(QString::fromStdString(host));
        ui->le_database->setText(QString::fromStdString(db));
        ui->le_port->setText(QString::number(port));
    }
}

DbSettings::~DbSettings()
{
    delete ui;
}

QString DbSettings::password() const
{
    return ui->le_password->text();
}

QString DbSettings::hostname() const
{
    return ui->le_host->text();
}

QString DbSettings::username() const
{
    return ui->le_username->text();
}

QString DbSettings::dbname() const
{
    return ui->le_database->text();
}

int DbSettings::port() const
{
    QString tmp;
    tmp = ui->le_port->text();
    bool ok;
    int res = tmp.toInt(&ok,10);
    return res;
}

void DbSettings::on_btn_set_app_clicked()
{
    QString tmp;
    tmp = ui->le_port->text();
    bool ok;
    tmp.toInt(&ok,10);

    if(ok){
        accept();
    } else{
        reject();
    }
}

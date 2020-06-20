#include "dbsettings.h"
#include "ui_dbsettings.h"

DbSettings::DbSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DbSettings)
{
    ui->setupUi(this);
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
    // called only after accept which checks convertibility
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
    if(ok)
    {
        accept();
    }
    else
    {
        reject();
    }
}

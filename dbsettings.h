#ifndef DBSETTINGS_H
#define DBSETTINGS_H

#include <QDialog>

namespace Ui {
class DbSettings;
}

class DbSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DbSettings(QWidget *parent = nullptr);
    ~DbSettings();

    QString dbname() const;
    QString username() const;
    QString password() const;
    QString hostname() const;
    int port() const;

private slots:
    void on_btn_set_app_clicked();

private:
    Ui::DbSettings *ui;
};

#endif // DBSETTINGS_H

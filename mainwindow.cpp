#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->tv_faqs,
            SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,
            SLOT(onTvFaqsItemClicked(QTreeWidgetItem*,int)));

    loadDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
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

    faq_data_ = std::make_unique<DataObject>();

    if(!prepareViewData()) return;

    initialiseTreeView();

    excuteQueryOnDb("SELECT * FROM questions");

    loadDataToFaqTreeView();
}

void MainWindow::initialiseDB()
{
    int port_setting;
    std::vector<QString> db_settings(4,0);

    loadSettings(db_settings,port_setting);

    db_instance_ = std::make_unique<DbHandler>(
                db_settings, port_setting);
}

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

bool MainWindow::prepareViewData()
{
    bool is_successful = true;
    QString all_errors = "";

    faq_data_->column_names_<< "ID" << "Question" << "Answer" << "Project";

    // load set with enumerator columns
    faq_data_->enum_cols.insert(4);
    faq_data_->enum_cols.insert(7);

    ui->lv_projects->clear();

    // Acessing data layer
    QSqlQuery query;
    if(query.exec("SELECT * FROM projects")){
        while(query.next()){
            faq_data_->projects_.insert(
            {query.value(0).toInt(),
             query.value(1).toString()});

            faq_data_->rev_projects_.insert(
            {query.value(1).toString().toStdString(),
             query.value(0).toInt()});

            QListWidgetItem * itm = new QListWidgetItem(query.value(1).toString());

            itm->setCheckState(Qt::Checked);
            itm->setData(0x0100,query.value(0));
            ui->lv_projects->addItem(itm);
        }
    } else {
        is_successful = false;
        all_errors += "Error loading projects list";
    }

    if(!is_successful)
    {
        QMessageBox msg;
        msg.setText(all_errors + db_instance_->lastError() + query.lastError().text());
        msg.exec();
    }

    return is_successful;
}

void MainWindow::initialiseTreeView()
{
    ui->tv_faqs->clear();
    ui->tv_faqs->setColumnCount(faq_data_->column_names_.size()-1);

    QStringList tmp;
    for(auto& item: faq_data_->column_names_)
    {
        tmp.push_back(item);
    }

    ui->tv_faqs->setHeaderLabels(tmp);
}

void MainWindow::excuteQueryOnDb(QString command)
{
    QSqlQuery query;
    if(query.exec(command)){
        while(query.next()){
            faq_data_->faq_values_.push_back(std::vector<QString>());

            for(int i = 0; i < faq_data_->column_names_.count(); i++){
                faq_data_->faq_values_.back().push_back(query.value(i).toString());
            }
        }
    } else{
        ui->statusbar->showMessage("Error executing query" + db_instance_->lastError());
    }
}

void MainWindow::loadDataToFaqTreeView()
{
    ui->tv_faqs->clear();

    int item_counter = 0;
    for(auto& mem_item : faq_data_->faq_values_)
    {
        QTreeWidgetItem * item = new QTreeWidgetItem(ui->tv_faqs);

        int col_counter = 0;
        int col_iter = 0;
        for(auto& column_string : mem_item){
            auto is_enum = faq_data_->enum_cols.find(col_iter);
            if(is_enum != faq_data_->enum_cols.end())
                item->setText(col_counter, faq_data_->projects_[column_string.toInt()]);
            else item->setText(col_counter,column_string);

            item->setData(col_counter, 0x0100, QVariant::fromValue<int>(item_counter));
            col_counter++;
            col_iter++;
        }

        item_counter++;
    }
}

void MainWindow::on_actionSettings_triggered()
{
    DbSettings dialog(this);
    dialog.exec();

    if(dialog.result() != QDialog::DialogCode::Accepted)
    {
        ui->statusbar->showMessage("Settings not updated");
    } else{
        // Writes it to 'settings.ini' file
        std::fstream ofs;
        ofs.open("settings.ini",std::ios::out);
        ofs << dialog.username().toStdString() << std::endl << dialog.password().toStdString()
            << std::endl << dialog.hostname().toStdString() << std::endl << dialog.dbname().toStdString()
            << std::endl << dialog.port();
        ofs.close();
        loadDatabase();
    }
}

void MainWindow::onTvFaqsItemClicked(QTreeWidgetItem *item, int column)
{
    int item_position_ =  item->data(column,0x0100).toInt();
    QString text;

    int i = 0;
    for(auto& field : faq_data_->faq_values_[item_position_])
    {
        auto is_enum = faq_data_->enum_cols.find(i);
        if(is_enum == faq_data_->enum_cols.end())
        {
            QString tmp = field;
            text += "<b>" +
                    faq_data_->column_names_.at(i) +
                    "</b><br>" +
                    tmp.replace("\n","<br>") + "<br><br>";
        } else
            text += "<b>" +
                    faq_data_->column_names_.at(i) +
                    "</b><br>" +
                    faq_data_->projects_.at(field.toInt()) + "<br><br>";

        i++;
    }

    ui->tb_faq_details->setText(text);
}

void MainWindow::on_btn_reset_clicked()
{
    for(int i = 0; i < ui->lv_projects->count(); i++)
        ui->lv_projects->item(i)->setCheckState(Qt::CheckState::Checked);
}


void MainWindow::on_btn_filter_clicked()
{
    QString query = "SELECT * FROM questions WHERE";

    QStringList checked_projects_;
    for(int i = 0; i < ui->lv_projects->count(); ++i)
    {
        if(ui->lv_projects->item(i)->checkState() == Qt::CheckState::Checked)
            checked_projects_.push_back(QString(" projectId='") + QString::number(ui->lv_projects->item(i)->data(0x0100).toInt()) +"'");
    }

    if(checked_projects_.size() > 0)
    {
        query+=" (";
        for(int i = 0; i < checked_projects_.size(); ++i)
        {
            if(i != 0) query += " OR";
            query += checked_projects_[i];
        }
        query += ")";
    }

    faq_data_->faq_values_.clear();
    excuteQueryOnDb(query);
    loadDataToFaqTreeView();
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionReconnect_triggered()
{
    loadDatabase();
}

#include "settings.h"
#include "ui_settings.h"
#include "application/application.h"
#include <QMessageBox>

settings::settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
}

settings::~settings()
{
    delete ui;
}

void settings::on_saveBtn_clicked()
{
    QString option = this->ui->sortByCombo_box->currentText();
    Application::loggedUser->getSettings()["sortBy"] =option;

    for(auto setting: Application::loggedUser->getSettings()){
        qDebug()<<setting.first << setting.second<<"\n";
    }
    QMessageBox* alert  = new QMessageBox();
    alert->setText("restart required to apply the changes!");
    alert->show();

}


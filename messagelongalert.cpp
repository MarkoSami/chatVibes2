#include "messagelongalert.h"
#include "ui_messagelongalert.h"

messageLongAlert::messageLongAlert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messageLongAlert)
{
    ui->setupUi(this);
}

messageLongAlert::~messageLongAlert()
{
    delete ui;
}

void messageLongAlert::on_pushButton_clicked()
{
    this->close() ;

}


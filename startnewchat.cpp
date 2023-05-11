#include "startnewchat.h"
#include "ui_startnewchat.h"
#include "application/application.h"
#include <QThread>
#include <QProgressBar>
#include <QTimer>
StartNewChat::StartNewChat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartNewChat)
{
    ui->setupUi(this);
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
}

StartNewChat::~StartNewChat()
{
    delete ui;
}

void StartNewChat::on_pushButton_clicked()
{

}


void StartNewChat::on_pushButton_5_clicked()
{
    this->close();
}


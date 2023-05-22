
#include "registerfrom.h"
#include "ui_registerfrom.h"
#include "lib/gui_lib.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QAbstractAnimation>
#include "logic/user.h"
#include "application/application.h"
#include <string>
#include <QKeyEvent>
#include "lib/utils.h"

Registerfrom::Registerfrom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registerfrom)
{
    ui->setupUi(this);
    GUI_lib::setUpWindow(this, "Register", ":/imgs/logo.png");
}

Registerfrom::~Registerfrom()
{
    delete ui;
}


void Registerfrom::on_pushButton_4_clicked()
{
    emit LoginClicked();
}


void Registerfrom::on_pushButton_3_clicked()
{
    std::string firstName = ui->firstNameLE->text().trimmed().toStdString();
    std::string lastName = ui->secondNameLE->text().trimmed().toStdString();
    std::string userName = ui->userNameLE->text().trimmed().toStdString();
    std::string password = ui->passwordLE->text().trimmed().toStdString();

    User *regUser = new User("",userName, firstName, lastName, password);
    QString ID = utils::convertAddressToString(regUser);
    regUser->setUserID(ID.mid(2).toStdString());

    if(Application::registerUser(regUser))
    {
        ui->RegisteredSuccessfully->setText("Registered successfully");

    }
    else qDebug()<< "Registeration failed";
}


void Registerfrom::on_backButton_clicked()
{
    emit BackClicked() ;
}

void Registerfrom::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        Registerfrom::on_pushButton_3_clicked();
    }
    else
    {
        QWidget::keyPressEvent(event);

    }
}

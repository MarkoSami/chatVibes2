#include "loginform.h"
#include "ui_loginform.h"
#include <QPixmap>
#include "lib/gui_lib.h"
#include "application/application.h"
#include <QTimer>
#include <QCoreApplication>
#include <QKeyEvent>
#include "lib/utils.h"

loginForm::loginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginForm)
{

    ui->setupUi(this);
    setWindowFlags( (windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    GUI_lib::setUpWindow(this, "Chat Vibes", ":/imgs/logo.png");

}

loginForm::~loginForm()
{
    delete ui;
}

void loginForm::on_pushButton_2_clicked()
{
    emit RegisterClicked();
}


void loginForm::on_LoginBtn_clicked()
{

    std::string userName = ui->userNameLE->text().trimmed().toStdString();
    std::string password = ui->passwordLE->text().trimmed().toStdString();

    if (userName.empty() || password.empty()) {
         ui->loggedInSuccessfully->setStyleSheet("color:red");
         ui->loggedInSuccessfully->setText("sorry username and password are required");

         return;
    }

    if(Application::loginUser(userName , password))
    {
        ui->loggedInSuccessfully->setStyleSheet("color:green");
        ui->loggedInSuccessfully->setText("Logged in successfully!");
        Application::loggedUser = Application::getLogInUser();
         // create a new QTimer instance and connect its timeout() signal to a lambda function
        QTimer* delayTimer = new QTimer(this);

        connect(delayTimer, &QTimer::timeout, [=]() {
            // close the current window
            Contact *newUserContact = new Contact("42",Application::loggedUser->getIMGpath() , Application::loggedUser->getUserName()) ;
            Application::loggedUser->setUserContact(newUserContact);    
            emit LoggedInSuccessfully();
            delayTimer->disconnect(); // disconnect the signal after emitting once
        });

        delayTimer->setSingleShot(true); // make the QTimer emit only once

         // start the timer with a 1 second interval

         delayTimer->start(150);

         // enter the application event loop
         QCoreApplication::processEvents();

    }
    else {
        ui->loggedInSuccessfully->setStyleSheet("color:red");
        ui->loggedInSuccessfully->setText("Login failed check your information again");
    }
}


void loginForm::on_backButton_clicked()
{
    emit BackClicked() ;
}

void loginForm::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        on_LoginBtn_clicked();
    }
    else
    {
        QWidget::keyPressEvent(event);

    }
}






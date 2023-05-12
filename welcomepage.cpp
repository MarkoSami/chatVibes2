
#include "welcomepage.h"
#include "ui_welcomepage.h"
#include "lib/filesystem_lib.h"
#include "QPropertyAnimation"
WelcomePage::WelcomePage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomePage)
{

    fileSystem_lib::loadData();
    QMetaObject::connectSlotsByName(this);
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(2,&logWin);
    ui->stackedWidget->insertWidget(3,&regWin);
    connect(&regWin, SIGNAL(LoginClicked()), this, SLOT(moveLogin()));
    connect(&regWin, SIGNAL(BackClicked()), this, SLOT(backHandler()));
    connect(&logWin, SIGNAL(BackClicked()), this, SLOT(backHandler()));
    connect(&logWin, SIGNAL(RegisterClicked()), this, SLOT(moveRegister()));
    connect(&logWin , SIGNAL(LoggedInSuccessfully()), this , SLOT(closedHandle()));

    setWindowOpacity(0.0);  // set initial opacity to 0

    // Create a QPropertyAnimation object to animate the window's opacity
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);  // set the animation duration to 500 milliseconds
    animation->setStartValue(0.0);  // set the start opacity value to 0
    animation->setEndValue(1.0);  // set the end opacity value to 1

    // Connect the finished() signal of the animation to a slot that shows the window
//    connect(animation, &QPropertyAnimation::finished, this, &MainWindow::show);

    animation->start(QAbstractAnimation::DeleteWhenStopped);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
//    mainWindowWin = new MainWindow();



}

WelcomePage::~WelcomePage()
{
    delete ui;
}

void WelcomePage::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void WelcomePage::moveLogin()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void WelcomePage::closedHandle() {
    this->close() ;
    MainWindow *mainWindowWin = new MainWindow() ;
    mainWindowWin->showMaximized();
}

void WelcomePage::moveRegister()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void WelcomePage::backHandler() {
    ui->stackedWidget->setCurrentIndex(1);
}

void WelcomePage::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void WelcomePage::on_pushButton_clicked()
{
      ui->stackedWidget->setCurrentIndex(1);
}


void WelcomePage::on_pushButton_7_clicked()
{
       this->close();
}


void WelcomePage::on_pushButton_8_clicked()
{
       if (window()->isMinimized()) {
           window()->showNormal();
       } else {
           window()->showMinimized();
       }
}


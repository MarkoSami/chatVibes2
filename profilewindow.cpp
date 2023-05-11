#include "profilewindow.h"
#include "ui_profilewindow.h"
#include <QPixmap>
#include <QFileDialog>
#include <application/application.h>


int const profileWindow::EXIT_CODE_REBOOT = -69;

QString file_path;
profileWindow::profileWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profileWindow)
{
    actionReboot = new QAction(this);
    actionReboot->setText(tr("Restart"));
    actionReboot->setStatusTip(tr("Restarts the application"));
    connect(actionReboot, &QAction::triggered, this, &profileWindow::rebootSlot);
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    if(Application::loggedUser != nullptr)
    {

        std::string loggedUserName = Application::loggedUser->getUserName();
        ui->lineEdit->setText(QString::fromStdString(loggedUserName));
        ui->ProfileImageLabel->setStyleSheet("border-image: url(" + QString::fromStdString(Application::loggedUser->getIMGpath()) + ");border-radius:8px");

    }
    ui->lineEdit_2->setText("Hello there! I'm using chatVibes");

}

profileWindow::~profileWindow()
{
    delete ui;
}

void profileWindow::on_pushButton_5_clicked()
{

    this->close();
}


void profileWindow::on_ProfileUploadBtn_clicked()
{
    // Open a file dialog and get the selected file
     file_path = QFileDialog::getOpenFileName(this, tr("Select Image"), QDir::homePath(), tr("Image files (*.png *.jpg *.jpeg *.bmp *.gif)"));

    // Check if a file was selected
    if (!file_path.isEmpty() && Application::loggedUser != nullptr) {
        // Upload the file to the server or perform other actions with it
        qDebug() << "File selected:" << file_path;
        ui->ProfileImageLabel->setStyleSheet("border-image: url(" + file_path + ");border-radius:8px");


    } else {
        // Handle case where no file was selected
        qDebug() << "No file selected.";
    }
}



void profileWindow::on_pushButton_clicked()
{
    qDebug() << "User name size: " << ui->lineEdit->text().size();
    qDebug() << "Image path size: " << file_path.toStdString().size();
    Application::loggedUser->setUserName(ui->lineEdit->text().toStdString());
    Application::loggedUser->setIMGpath(file_path.toStdString());
    Application::loggedUser->getUserContact()->setImgPath(file_path.toStdString());
    Application::updatePhoto(Application::loggedUser->getUserName(),Application::loggedUser->getIMGpath()) ;

}


void profileWindow::on_pushButton_2_clicked()
{
    emit rebootSlot();
}


void profileWindow::rebootSlot(){
    qDebug()<<"Performing Application reboot";
    qApp->exit( profileWindow::EXIT_CODE_REBOOT);
}

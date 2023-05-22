#include "addstory.h"
#include "ui_addstory.h"
#include <QFileDialog>
#include "logic/story.h"
#include "application/application.h"

AddStory::AddStory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStory)
{
    ui->setupUi(this);
}

AddStory::~AddStory()
{
    delete ui;
}
QString img_path;

void AddStory::on_pushButton_clicked()
{
    // Open a file dialog and get the selected file
    img_path = QFileDialog::getOpenFileName(this, tr("Select Image"), QDir::homePath(), tr("Image files (*.png *.jpg *.jpeg *.bmp *.gif)"));
    ui->pushButton->setText("Photo Uploaded !");
    // Check if a file was selected
    if (!img_path.isEmpty()) {
        // Upload the file to the server or perform other actions with it
        qDebug() << "File selected:" << img_path;
    } else {
        // Handle case where no file was selected
        qDebug() << "No file selected.";
    }
}


void AddStory::on_pushButton_2_clicked()
{
    ui->label->setContentsMargins(5,0,0,0);
    Story *newStory = new Story(ui->lineEdit->text() , img_path , Application::loggedUser->getUserContact());
    if (ui->lineEdit->text().isEmpty() && img_path.isEmpty()) {
        ui->label->setText("at least fill one field");
        ui->label->setStyleSheet("color:red") ;
        return ;
    }
    Application::stories[Application::loggedUser->getUserID()].push_back(newStory) ;

    img_path = "" ;
    ui->lineEdit->setText("");
    emit AddStoryhandler(newStory);
    ui->label->setStyleSheet("color:green") ;
    ui->label->setText("Story published successfully");
    qDebug()<<Application::stories[Application::loggedUser->getUserName()].size();
}


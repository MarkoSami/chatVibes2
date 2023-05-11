#include "addcontact.h"
#include "logic/contact.h"
#include "ui_addcontact.h"
#include <QFileDialog>
#include <QPropertyAnimation>
#include <QEvent>
#include "application/application.h"
#include <QString>

AddContact::AddContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddContact)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
}

AddContact::~AddContact()
{
    delete ui;
}





void AddContact::on_pushButton_10_clicked()
{
     this->close();
}




void AddContact::on_pushButton_2_clicked()
{

     std::string id = ui->lineEdit_4->text().toStdString(); // assign unique id to each contact
     std::string name = ui->lineEdit_5->text().toStdString();
     QString imgPath = img_path;


     if ((Application::loggedUser) != nullptr) {
         if (id != "" && name != "") {
        Contact *newContact = new Contact(id, imgPath.toStdString(), name);
        Conversation* newConversation = new Conversation(newContact , false , newContact->getName());
        Application::loggedUser->addContact(newContact);
        newConversation->getReceiver()->setImgPath(Application::renderWithPhoto(newContact->getName()));
        Application::loggedUser->addNewConversation(newConversation);
        emit renderConversation() ;
     }
     }

}





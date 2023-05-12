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
    std::string id = ui->contactName->text().toStdString(); // assign unique id to each contact
    std::string messageName = ui->messageName->text().toStdString();

    if ((Application::loggedUser) != nullptr) {
        if (id != "" && messageName != "") {
            Contact *newContact = new Contact(id); // mark // username
            newContact->setName(newContact->getID());
            newContact->setID(Application::findContactID(newContact->getName()));
            Conversation* newConversation = new Conversation(newContact , false , newContact->getName());
            newConversation->getReceiver()->setIsAdded(true);
            Application::loggedUser->addNewConversation(newConversation);

            Message *messageText = new Message(Application::loggedUser->getUserID(), messageName, newConversation->getReceiver()->getID() , QDateTime::currentDateTime(), false, false);
            newConversation->addNewMessage(messageText);

            emit renderConversationAnonymously();

            Conversation* crnt = newConversation;
            QClickableGroupBox* gb = crnt->getConversationGroupBoxAddress();
            QString addrs = gb->property("labelAddress").toString();
            QLabel* messageLabelAddress = (QLabel*)utils::convertStringToaddress(addrs);

            messageLabelAddress->setText(messageText->getMessageTxt().c_str());


//            QClickableGroupBox* ConversationgroubBoxAddress  = Application::currentConversation->getConversationGroupBoxAddress();

            Conversation *receiverConv = Application::getReceiverConversation(newConversation->getReceiver()->getName());
            if(receiverConv != nullptr)
            receiverConv->addNewMessage(messageText);



        }
    }
}


void StartNewChat::on_pushButton_5_clicked()
{
    this->close();
}



#include "message.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QGroupBox>
#include <QDateTime>
#include <string>

Message::Message(std::string _ID, std::string _messageTxt, std::string _receiverID, QDateTime _sendDate, bool _seen , bool _Favourite = false,bool _deleted  )
{
    this->ID = _ID;
    this->messageTxt = _messageTxt;
    this->receiverID = _receiverID;
    this->sendDate = _sendDate;
    this->seen = _seen;
    this->Favourite = _Favourite ;
    this->deleted = _deleted;
}



bool Message::isDeleted(){
    return this->deleted;
}

std::list<Contact *>& Message::getMessageFavBy() {
    return this->messageFavBy ;
}

void Message::setMessageFavBy(Contact * name) {
    this->messageFavBy.push_back(name);
}

void Message::toggleDeleted(){
    this->deleted = !this->deleted;
}

bool Message::isFavourite() {
    return Favourite;
}
void Message::toggleFavourite(){
    this->Favourite = !this->Favourite;
}


std::string Message::getID(){
    return this->ID;
}

void rendermessageReciever(QGroupBox* layoutSpecified , std::string messageText , std::string imgPath) {
    QHBoxLayout *hLayout = new QHBoxLayout;
    QHBoxLayout *hLayoutParent = new QHBoxLayout;

    // Add QLabel widgets to the layout
    QLabel *ProfilePic = new QLabel();
    ProfilePic->setSizePolicy(QSizePolicy::Fixed , QSizePolicy::Fixed);
    ProfilePic->setMinimumHeight(30); ProfilePic->setMinimumWidth(30);
    ProfilePic->setStyleSheet("image: url(:/imgs/Profile (2).png);");

    QLabel *textMsg = new QLabel("mmmmm Test :");
    textMsg->setSizePolicy(QSizePolicy::Fixed , QSizePolicy::Fixed);
    textMsg->setMinimumHeight(30); textMsg->setMinimumWidth(70);
    textMsg->setStyleSheet("color : white ;font-weight :bold;font-size : 16px ;");

    // Add the QLabel to the child QGroupBox layout
    hLayout->addWidget(ProfilePic);
    hLayout->addWidget(textMsg);

    // Add a horizontal spacer to the parent QGroupBox layout
    QSpacerItem *hSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);


    // Create a new QGroupBox with the child QHBoxLayout as its layout
    QGroupBox *hGroupBox = new QGroupBox();
    hGroupBox->setMinimumHeight(60);
    hGroupBox->setStyleSheet("background :#161a1d ;");
    hLayout->setSpacing(30);
    hLayout->setContentsMargins(20,9,20,9);
    hGroupBox->setLayout(hLayout);

    // Add the child QGroupBox to the parent QGroupBox layout
    hLayoutParent->addItem(hSpacer);
    hLayoutParent->addWidget(hGroupBox);

    // Set the parent QGroupBox layout and style sheet
    QGroupBox *hGroupBoxParent = new QGroupBox();
    hGroupBoxParent->setLayout(hLayoutParent);
}

void rendermessageSender(QGroupBox* layoutSpecified , std::string messageText , std::string imgPath) {
    QHBoxLayout *hLayout = new QHBoxLayout;
    QHBoxLayout *hLayoutParent = new QHBoxLayout;

    // Add QLabel widgets to the layout
    QLabel *ProfilePic = new QLabel();
    ProfilePic->setSizePolicy(QSizePolicy::Fixed , QSizePolicy::Fixed);
    ProfilePic->setMinimumHeight(30); ProfilePic->setMinimumWidth(30);
    ProfilePic->setStyleSheet("image: url(:/imgs/Profile (2).png);");

    QLabel *textMsg = new QLabel("mmmmm Test :");
    textMsg->setSizePolicy(QSizePolicy::Fixed , QSizePolicy::Fixed);
    textMsg->setMinimumHeight(30); textMsg->setMinimumWidth(70);
    textMsg->setStyleSheet("color : white ;font-weight :bold;font-size : 16px ;");

    // Add the QLabel to the child QGroupBox layout
    hLayout->addWidget(ProfilePic);
    hLayout->addWidget(textMsg);

    // Add a horizontal spacer to the parent QGroupBox layout
    QSpacerItem *hSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);


    // Create a new QGroupBox with the child QHBoxLayout as its layout
    QGroupBox *hGroupBox = new QGroupBox();
    hGroupBox->setMinimumHeight(60);
    hGroupBox->setStyleSheet("background :#161a1d ;");
    hLayout->setSpacing(30);
    hLayout->setContentsMargins(20,9,20,9);
    hGroupBox->setLayout(hLayout);

    // Add the child QGroupBox to the parent QGroupBox layout
    hLayoutParent->addWidget(hGroupBox);
    hLayoutParent->addItem(hSpacer);
    // Set the parent QGroupBox layout and style sheet
    QGroupBox *hGroupBoxParent = new QGroupBox();
    hGroupBoxParent->setLayout(hLayoutParent);
}



std::string Message::getMessageTxt()
{
    return messageTxt;
}

QDateTime Message::getSendDate()
{
    return sendDate;
}

std::string Message::getReceiverId()
{
    return receiverID;
}

bool Message::isSeen()
{
    return seen;
}

void Message::setSeenStatus(bool seenStatus)
{
    seen = seenStatus;
}


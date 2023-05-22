#include "mainwindow.h"
#include "profilewindow.h"
#include "ui_mainwindow.h"
#include "lib/gui_lib.h"
#include<QString>
#include <QScreen>
#include <QPixmap>
#include <QDateTime>
#include "lib/filesystem_lib.h"
#include "addcontact.h"
#include <QPropertyAnimation>
#include "startnewchat.h"
#include "application/application.h"
#include <QScrollBar>
#include "logic/conversation.h"
#include "logic/message.h"
#include "customGUI/qclickablegroubox.h"
#include <QTimer>
#include <QMessageBox>
#include "lib/gui_render.h"
#include <QChar>
#include <algorithm>
#include "lib/utils.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    ui->setupUi(this);
    // Set the window to open as full screen

    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->sendMessageLineEdit, &QLineEdit::returnPressed,
            this, &MainWindow::on_pushButton_7_clicked);

    connect(ui->searchFavMsg, &QLineEdit::textChanged,
            this, &MainWindow::on_searchForFav_clicked);

    connect(ui->ContactSearchLE, &QLineEdit::textChanged,
            this, [=]() {
                std::string keyword = ui->ContactSearchLE->text().toStdString();
                searchForContact(keyword);
            });



    GUI_lib::setUpWindow(this, "Chat Vibes", ":/imgs/logo.png");
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    ui->scrollAreaWidgetContents->setContentsMargins(9,20,9,40);
    ui->scrollArea_2->verticalScrollBar()->setSingleStep(6);

    // Create a QPropertyAnimation object to animate the window's opacity
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(150);  // set the animation duration to 500 milliseconds
    animation->setStartValue(0.0);  // set the start opacity value to 0
    animation->setEndValue(1.0);  // set the end opacity value to 1

    // Connect the finished() signal of the animation to a slot that shows the window
    //    connect(animation, &QPropertyAnimation::finished, this, &MainWindow::show);

    animation->start(QAbstractAnimation::DeleteWhenStopped);


    ///////////////////////
    GUI_render::renderConversations(this,false);


}

Ui::MainWindow* MainWindow::getUI(){
    return this->ui;
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::renderLoggedUserStory(Story *newStory) {

    QLayout* layout = ui->horizontalGroupBox_3->layout();
    QLayoutItem* item;
    while((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QClickableGroupBox* storyBox = GUI_render::renderStory(newStory,Application::loggedUser->getUserName());
    if (Application::stories[Application::loggedUser->getUserID()].size() > 1) {
         MainWindow::handleStoryClicked(storyBox , Application::stories[Application::loggedUser->getUserID()] , this);
    }

    MainWindow::connect(storyBox, &QClickableGroupBox::clicked, [=]() {
        MainWindow::handleStoryClicked(storyBox , Application::stories[Application::loggedUser->getUserID()] , this);
    });
    ui->horizontalGroupBox_3->layout()->addWidget(storyBox) ;
}


void MainWindow::handleClickedConversation(QGroupBox *renderConversation) {


    // Set the current index to 1 to show a loading screen
    ui->stackedWidget->setCurrentIndex(1);

    // Create a QTimer object and set it to a single-shot timer with a 2-second delay
    QTimer::singleShot(1, [=]() {

        if (!renderConversation) {
            qDebug() << "Render conversation is null";
            return;
        }

        // Create a stringstream object from the string.
        void* address  = utils::convertStringToaddress(renderConversation->objectName());

        // Cast the void* pointer to the desired type.
        Conversation* conversation = static_cast<Conversation*>(address);

        qDebug()<< (Application::currentConversation );
        Application::currentConversation =  conversation;
        qDebug()<< (Application::currentConversation );

        if (!Application::currentConversation->getReceiver()->getIsAdded()) {
            ui->pushButton_5->setStyleSheet("image: url(:/imgs/addIcon.png)");
            ui->pushButton_5->setCursor(Qt::PointingHandCursor);
        }

        else {
            ui->pushButton_5->setStyleSheet("");
            ui->pushButton_5->setCursor(Qt::ArrowCursor);
        }


        QLayoutItem *item;
        while ((item = ui->verticalGroupBox_3->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        ui->contactsCont->layout() ;
        ui->horizontalLayout_5->layout()->setSpacing(10);
        ui->ContactName->setText(conversation->getName().c_str());

        QString IMG_PATH =QString::fromStdString(conversation->getReceiver()->getImgPath());
        QSize imgMaxSize = (IMG_PATH == ":/imgs/Profile (2).png")? *new QSize(40,40) : *new QSize(50,60);

        if(IMG_PATH == ":/imgs/Profile (2).png")
            ui->ContactIMG->setMaximumSize(imgMaxSize);

        ui->ContactIMG->setMinimumSize(imgMaxSize);

        QString imgType = IMG_PATH == ":/imgs/Profile (2).png"? "image" : "border-image";
        ui->ContactIMG->setStyleSheet( imgType+  ":url(" + IMG_PATH + ");border-radius:8px");
        for (auto &conv : conversation->getMessages()) {
            qDebug() << conv->getMessageFavBy().size() << conv->getMessageTxt() ;
            ui->verticalGroupBox_3->layout()->addWidget(Application::renderMessage(conv)->outerLayout);
        }

        // Set the current index to 2 to show the conversation
        ui->stackedWidget->setCurrentIndex(3);

        QTimer::singleShot(0, this, [=]() {
            int max = ui->scrollArea_2->verticalScrollBar()->maximum();
            ui->scrollArea_2->verticalScrollBar()->setValue(max);
        });

    });
}






void MainWindow::on_pushButton_3_clicked()
{

    //    Application::conversations.push(Conversation(Contact("sdfs")));
    fileSystem_lib::saveData();
    this->close();
}

void MainWindow::renderContactMain() {

    Conversation* conversationPtr = (Application::loggedUser->getConversations().top());

    // Create the QClickableGroupBox widget
    QClickableGroupBox *conv = Application::renderConversation(conversationPtr)->outerLayout;
    conversationPtr->setConversationGroupBoxAddress(conv);
    conv->setObjectName(utils::convertAddressToString(conversationPtr));

    connect(conv, &QClickableGroupBox::clicked, [=]() {
        handleClickedConversation(conv);
    });

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->contactsCont->layout());
    if (layout) {
         layout->insertWidget(0, conv);
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    if (this->isMaximized()) {
        this->showNormal();
    } else {
        this->showMaximized();
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if (window()->isMinimized()) {
        window()->showNormal();
    } else {
        window()->showMinimized();
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    if (!Application::currentConversation->getReceiver()->getIsAdded()) {
    addContactWin = new AddContact() ;
        addContactWin->setIDAuto(QString::fromStdString(Application::currentConversation->getReceiver()->getID()));
    addContactWin->show();
    connect(addContactWin, SIGNAL(renderConversation()), this, SLOT(dissappearIcon()));
    }

}

void MainWindow::dissappearIcon() {
    ui->pushButton_5->setStyleSheet("");
    ui->ContactName->setText(QString::fromStdString(Application::currentConversation->getReceiver()->getName()));

}

void MainWindow::on_pushButton_6_clicked()
{
    profWin = new profileWindow();
    profWin->show();
}


void MainWindow::on_pushButton_clicked()
{
    StartNewChatWin = new StartNewChat();
    StartNewChatWin->show();
    connect(StartNewChatWin, SIGNAL(renderConversationAnonymously()), this, SLOT(renderContactMain()));
}



void MainWindow::on_pushButton_7_clicked()
{
    QString textMsg = ui->sendMessageLineEdit->text();
    int DelayHandler ;
    if (textMsg.size() > 30000) {
        messageLongAlertWin = new messageLongAlert() ;
        messageLongAlertWin->show() ;
    }
    else {
        if (!textMsg.isEmpty()) { // check if the text is not empty
            // Make a copy of the original stack
            std::stack<Conversation*> tempConversations ;


            Message *messageTest = new Message(Application::loggedUser->getUserName(), textMsg.toStdString(), Application::currentConversation->getReceiver()->getName(), QDateTime::currentDateTime(), false, false);
            Application::currentConversation->addNewMessage(messageTest);

            Conversation* crnt = Application::currentConversation;
            QClickableGroupBox* gb = crnt->getConversationGroupBoxAddress();
            QString addrs = gb->property("labelAddress").toString();
            QLabel* messageLabelAddress = (QLabel*)utils::convertStringToaddress(addrs);

            messageLabelAddress->setText(messageTest->getMessageTxt().c_str());
            QClickableGroupBox* ConversationgroubBoxAddress  = Application::currentConversation->getConversationGroupBoxAddress();

            Conversation *receiverConv = Application::getReceiverConversation(Application::currentConversation->getReceiver()->getName());
            if(receiverConv != nullptr)
                receiverConv->addNewMessage(messageTest);

            ui->verticalGroupBox_3->layout()->addWidget(Application::renderMessage(messageTest)->outerLayout);

            ui->sendMessageLineEdit->setText("");
            DelayHandler = messageTest->getMessageTxt().size() ;
            QTimer::singleShot(DelayHandler = DelayHandler <= 300 ? DelayHandler + 100 : 300 , [=](){
                ui->scrollArea_2->verticalScrollBar()->setValue(ui->scrollArea_2->verticalScrollBar()->maximum());
            });

            utils::moveToTop(Application::loggedUser->getConversations(),Application::currentConversation);
            QLayout* layout = ui->contactsCont->layout();
            QLayoutItem* item;

            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget(); // delete the widget associated with the item
                delete item; // delete the item itself
            }
            GUI_render::renderConversations(this,false);

        }

      }

 }


void MainWindow::on_addNewStoryBtn_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

    GUI_render::renderStories(this);
}


void MainWindow::on_viewFavMsg_clicked()
{
    QLayout* layout = ui->favMessageCont->layout();
    QLayoutItem* item;

    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget(); // delete the widget associated with the item
        delete item; // delete the item itself
    }

    ui->stackedWidget_2->setCurrentIndex(2);
    ui->scrollArea_4->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    std::stack<Conversation *> conv = Application::loggedUser->getConversations();
    while(!conv.empty())
    {
      std::list<Message* > messages = conv.top()->getMessages();
      for(auto &msg : messages)
      {
        bool isFavedByUser = false ;

        for (auto &putFavUser : msg->getMessageFavBy()) {
                if (putFavUser->getName() == Application::loggedUser->getUserContact()->getName() && msg->isFavourite()) {
                    isFavedByUser = true;
                }
        }
         if(isFavedByUser )
        {
                QLabel *favMessage = GUI_render::renderFavMessage(*msg) ;
                ui->favMessageCont->layout()->addWidget(favMessage);
        }
      }
      conv.pop();
    }
}

void MainWindow::on_backSotryBtn_clicked()
{
    MainWindow::BackBtnStoryHandle(this);
}


void MainWindow::on_searchForFav_clicked()
{
    QLayout* layout = ui->favMessageCont->layout();
    QLayoutItem* item;

    while ((item = layout->takeAt(0)) != nullptr) {
      delete item->widget(); // delete the widget associated with the item
      delete item; // delete the item itself
    }

    QString search_keyword = ui->searchFavMsg->text();
    std::stack<Conversation *> conv = Application::loggedUser->getConversations();
    while(!conv.empty())
    {
        std::list<Message* > messages = conv.top()->getMessages();
        for(auto msg : messages)
        {
            bool isFavedByUser = false ;

            for (auto &putFavUser : msg->getMessageFavBy()) {
                    if (putFavUser->getName() == Application::loggedUser->getUserContact()->getName() && msg->isFavourite()) {
                        isFavedByUser = true;
                    }
            }
            if(isFavedByUser&& Application::isSubstringFound(msg->getMessageTxt(), search_keyword.toStdString()) )
            {
                QLabel *favMessage = GUI_render::renderFavMessage(*msg) ;
                ui->favMessageCont->layout()->addWidget(favMessage);
            }
        }
        conv.pop();
    }
}

void MainWindow::on_NextStoryBtn_clicked()
{
    MainWindow::NextBtnStoryHandle(this);
}


void MainWindow::on_pushButton_8_clicked()
{
    addStoryWin = new AddStory() ;
    addStoryWin->show() ;
    connect(addStoryWin, SIGNAL(AddStoryhandler(Story*)), this, SLOT(renderLoggedUserStory(Story*)));
}


void MainWindow::on_pushButton_9_clicked()
{
    this->ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::searchForContact(std::string key_word)
{

    std::stack<Conversation* > convs = Application::loggedUser->getConversations();
    QLayout* layout = ui->contactsCont->layout();
    QLayoutItem* item;

    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget(); // delete the widget associated with the item
        delete item; // delete the item itself
    }
    while(!convs.empty())
    {
        if(Application::isSubstringFound(convs.top()->getName(), key_word))
        {

            // Create the QClickableGroupBox widget
            QClickableGroupBox *conv = Application::renderConversation(convs.top())->outerLayout;
            conv->setObjectName(utils::convertAddressToString(convs.top()));

            connect(conv, &QClickableGroupBox::clicked, [=]() {
                handleClickedConversation(conv);
            });

            ui->contactsCont->layout()->addWidget(conv);
        }
        convs.pop();
    }


}




void MainWindow::on_view_settings_btn_clicked()
{
    this->settingsWin = new settings();
    GUI_lib::setUpWindow(settingsWin,"ChatVibes|Settings",":/imgs/settings.png");
    settingsWin->show();
}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "profilewindow.h"
#include "addcontact.h"
#include "startnewchat.h"
#include "messagelongalert.h"
#include <QGroupBox>
#include "logic/story.h"
#include <list>
#include "ui_mainwindow.h"
#include "application/application.h"
#include "addstory.h"

        QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow* getUI();




private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked()  ;

    void on_pushButton_7_clicked();

    void renderContactMain();


    void on_addNewStoryBtn_clicked();

    void on_backSotryBtn_clicked();

    void on_NextStoryBtn_clicked();

    void on_pushButton_8_clicked();

    void on_viewFavMsg_clicked();

    void on_searchForFav_clicked();

    void renderLoggedUserStory(Story *newStory)  ;

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void searchForContact(std::string key_word);


private:
    Ui::MainWindow *ui;
    AddContact *addContactWin ;
    StartNewChat *StartNewChatWin;
    profileWindow *profWin;
    messageLongAlert *messageLongAlertWin ;
    AddStory *addStoryWin ;

public slots:
    void handleClickedConversation(QGroupBox*);

    static void handleStoryClicked(QGroupBox* , std::list<Story*> storiesList , MainWindow* mainWindow){

        Story *story = storiesList.front() ;
        Application::currentStory = story ;
        Application::currentStoryList = storiesList ;
        mainWindow->getUI()->storyCaption->setText("");
        mainWindow->getUI()->picStory->setStyleSheet("");
        mainWindow->getUI()->picStory->setText("");
        if (story->getImgPath().isEmpty()) {
            mainWindow->getUI()->picStory->setText(story->getCaption());
            mainWindow->getUI()->picStory->setAlignment(Qt::AlignCenter);
            mainWindow->getUI()->picStory->setStyleSheet("font-size:50px ; font-weight:bold ; color :white ");
            mainWindow->getUI()->stackedWidget->setCurrentIndex(2);
            return;
        }
        mainWindow->getUI()->storyCaption->setText(story->getCaption());
        mainWindow->getUI()->picStory->setStyleSheet("image: url(" + story->getImgPath() + ")");
        mainWindow->getUI()->stackedWidget->setCurrentIndex(2);
    }

    static void BackBtnStoryHandle(MainWindow* mainWindow) {
        Story *PrevStory = nullptr;
        for (auto story : Application::currentStoryList) {
            if (story == Application::currentStory) {
                break;
            }
            PrevStory = story ;
        }

        if (PrevStory == nullptr) {
            PrevStory = Application::currentStoryList.back() ;
        }
        Application::currentStory = PrevStory ;
        mainWindow->getUI()->storyCaption->setText("");
        mainWindow->getUI()->picStory->setStyleSheet("");
        mainWindow->getUI()->picStory->setText("");
        if (PrevStory->getImgPath().isEmpty()) {
            mainWindow->getUI()->picStory->setText(PrevStory->getCaption());
            mainWindow->getUI()->picStory->setAlignment(Qt::AlignCenter);
            mainWindow->getUI()->picStory->setStyleSheet("font-size:50px ; font-weight:bold ; color :white ");
            return;
        }
        mainWindow->getUI()->storyCaption->setText(PrevStory->getCaption());
        mainWindow->getUI()->picStory->setStyleSheet("image: url(" + PrevStory->getImgPath() + ")");
        mainWindow->getUI()->stackedWidget->setCurrentIndex(2);
    }

    static void NextBtnStoryHandle(MainWindow* mainWindow) {
        Story *NextStory = nullptr;
        int i = 0 ;
        for (auto story : Application::currentStoryList) {
            if (i == 1) {
                NextStory = story ;
                break ;
            }
            if (story == Application::currentStory) {
                i++ ;
            }
        }
        if (NextStory == nullptr) {
            NextStory = Application::currentStoryList.front() ;
        }
        Application::currentStory = NextStory ;
        mainWindow->getUI()->storyCaption->setText("");
        mainWindow->getUI()->picStory->setStyleSheet("");
        mainWindow->getUI()->picStory->setText("");
        if (NextStory->getImgPath().isEmpty()) {
            mainWindow->getUI()->picStory->setText(NextStory->getCaption());
            mainWindow->getUI()->picStory->setAlignment(Qt::AlignCenter);
            mainWindow->getUI()->picStory->setStyleSheet("font-size:50px ; font-weight:bold ; color :white ");
            return;
        }
        mainWindow->getUI()->storyCaption->setText(NextStory->getCaption());
        mainWindow->getUI()->picStory->setStyleSheet("image: url("+NextStory->getImgPath()+")");
        mainWindow->getUI()->stackedWidget->setCurrentIndex(2);
    }
};

#endif // MAINWINDOW_H

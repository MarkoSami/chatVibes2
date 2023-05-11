
#ifndef GUI_LIB_H
#define GUI_LIB_H
#include<QIcon>
#include<string.h>
#include<QMainWindow>
#include<QString>
#include<string.h>
#include<QIcon>

class GUI_lib
{
public:
    GUI_lib();
    // this function is used to set up any window in this application
    static void setUpWindow(QWidget *window,std::string  windowTitle,std::string imagePath){
        window->setWindowIcon(QIcon(imagePath.c_str()));
        window->setWindowTitle(QString(windowTitle.c_str()));
    }
};

#endif // GUI_LIB_H

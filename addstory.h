#ifndef ADDSTORY_H
#define ADDSTORY_H

#include <QDialog>
#include "logic/story.h"

namespace Ui {
class AddStory;
}

class AddStory : public QDialog
{
    Q_OBJECT

public:
    explicit AddStory(QWidget *parent = nullptr);
    ~AddStory();

signals:
    void AddStoryhandler(Story *loggedUserStory) ;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::AddStory *ui;
};

#endif // ADDSTORY_H

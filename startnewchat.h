#ifndef STARTNEWCHAT_H
#define STARTNEWCHAT_H

#include <QDialog>

namespace Ui {
class StartNewChat;
}

class StartNewChat : public QDialog
{
    Q_OBJECT

public:
    explicit StartNewChat(QWidget *parent = nullptr);
    ~StartNewChat();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::StartNewChat *ui;
};

#endif // STARTNEWCHAT_H

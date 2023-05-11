#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QDialog>
#include "registerfrom.h"
#include "loginform.h"
#include "profilewindow.h"
#include "mainwindow.h"

namespace Ui {
class WelcomePage;
}

class WelcomePage : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomePage(QWidget *parent = nullptr);
    ~WelcomePage();

private slots:
    void on_pushButton_2_clicked();
    void moveLogin();
    void backHandler();
    void moveRegister();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void closedHandle() ;
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();


private:
    Ui::WelcomePage *ui;
    Registerfrom regWin ;
    loginForm logWin ;
};

#endif // WELCOMEPAGE_H

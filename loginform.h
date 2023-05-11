#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QDialog>
class QKeyEvent;

namespace Ui {
class loginForm;
}

class loginForm : public QWidget
{
    Q_OBJECT

public:
    explicit loginForm(QWidget *parent = nullptr);
    ~loginForm();




private:
    Ui::loginForm *ui;

signals:
    void RegisterClicked();
    void LoggedInSuccessfully();
    void BackClicked() ;

private slots:
    void on_pushButton_2_clicked();
    void on_LoginBtn_clicked();
    void on_backButton_clicked();
    void keyPressEvent(QKeyEvent *event);


};

#endif // LOGINFORM_H

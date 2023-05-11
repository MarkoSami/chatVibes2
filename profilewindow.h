#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QWidget>

namespace Ui {
class profileWindow;
}

class profileWindow : public QWidget
{
    Q_OBJECT

public:
    explicit profileWindow(QWidget *parent = nullptr);
    ~profileWindow();
     static int const EXIT_CODE_REBOOT;
    signals:
    void showWelcomePage();
    void exitMainWindow();


private slots:
    void on_pushButton_5_clicked();
    void on_ProfileUploadBtn_clicked();
    void on_pushButton_clicked();
    void rebootSlot();
    void on_pushButton_2_clicked();

private:
    Ui::profileWindow *ui;
    QAction *actionReboot;

};

#endif // PROFILEWINDOW_H

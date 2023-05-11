#ifndef REGISTERFROM_H
#define REGISTERFROM_H

#include <QDialog>

namespace Ui {
class Registerfrom;
}

class Registerfrom : public QDialog
{
    Q_OBJECT

public:
    explicit Registerfrom(QWidget *parent = nullptr);
    ~Registerfrom();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_backButton_clicked();
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Registerfrom *ui;

signals:
    void LoginClicked();
    void BackClicked() ;
};

#endif // REGISTERFROM_H

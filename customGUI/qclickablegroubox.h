#ifndef QCLICKABLEGROUBOX_H
#define QCLICKABLEGROUBOX_H

#include <QGroupBox>
#include <QMenu>

class QClickableGroupBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit QClickableGroupBox(QWidget *parent = nullptr);
signals: void showAddContactIconHandler();


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QMenu *m_contextMenu;
    QAction *m_favAction;
    QAction *m_deleteAction;

    void createContextMenu();

private slots:
    void handleFavAction();
    void handleDeleteAction();

signals:
    void clicked();
    void doubleClickDetected();
};

#endif // QCLICKABLEGROUBOX_H

#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QToolButton>

class QICon;
class QAction;
class ToolButton: public QToolButton
{
        Q_OBJECT

public:
        explicit ToolButton(const QIcon& normalIcon, const QIcon& hoverIcon, const QIcon& checkIcon, QWidget *parent = 0);
        void enterEvent(QEvent *e);
        void leaveEvent(QEvent *e);
        void mousePressEvent(QMouseEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);

signals:

private slots:
        void changeState(bool checked);
private:
        QIcon normalIcon, hoverIcon, checkIcon;
        bool isInside;
};

#endif


#ifndef FRAME_H
#define FRAME_H

#include <QWidget>

class QToolBar;
class QGridLayout;
class Frame : public QWidget
{
    Q_OBJECT
public:
    explicit Frame(QWidget *parent = 0);
    
signals:
    
public slots:
    
protected:
    QToolBar *toolbar;
    QGridLayout *mainlayout;
};

#endif // FRAME_H

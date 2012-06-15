#ifndef SIMWINDOW_H
#define SIMWINDOW_H

#include "Frame.h"

class SimWidget;
class SimWindow : public Frame
{
    Q_OBJECT
public:
    explicit SimWindow(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    SimWidget *simWidget;
};

#endif // SIMWINDOW_H

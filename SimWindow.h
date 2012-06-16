#ifndef SIMWINDOW_H
#define SIMWINDOW_H

#include "Frame.h"

class SimWidget;
class ToolButton;
class SimWindow : public Frame
{
    Q_OBJECT
public:
    explicit SimWindow(QWidget *parent = 0);
    SimWidget* getWidget();

signals:
    void editCode();

public slots:

private:
    SimWidget *simWidget;
    ToolButton *editButton;
};

#endif // SIMWINDOW_H

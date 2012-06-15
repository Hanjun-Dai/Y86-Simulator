#include "SimWindow.h"
#include "SimWidget.h"
#include <QGridLayout>

SimWindow::SimWindow(QWidget *parent) :
    Frame(parent)
{
    simWidget = new SimWidget;
    mainlayout->addWidget(simWidget, 1, 0);
}

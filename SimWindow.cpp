#include "SimWindow.h"
#include "SimWidget.h"
#include <QGridLayout>
#include "ToolButton.h"
#include <QToolBar>

SimWidget* SimWindow::getWidget()
{
    return simWidget;
}

SimWindow::SimWindow(QWidget *parent) :
    Frame(parent)
{
    QIcon i1(":/edit_normal.png"), i2(":/edit_hover.png"), i3(":/edit_check.png");
    editButton = new ToolButton(i1, i2, i3);
    toolbar->addWidget(editButton);

    QToolButton *resetButton = new QToolButton;
    toolbar->addWidget(resetButton);

    QToolButton *singleStepButton = new QToolButton;
    toolbar->addWidget(singleStepButton);

    simWidget = new SimWidget;
    mainlayout->addWidget(simWidget, 1, 0);

    connect(editButton, SIGNAL(clicked()), SIGNAL(editCode()));

    connect(resetButton, SIGNAL(clicked()), simWidget, SLOT(reset()));
    connect(singleStepButton, SIGNAL(clicked()), simWidget, SLOT(singleStep()));
}

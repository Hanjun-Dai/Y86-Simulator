#include "EditorWindow.h"
#include <QGridLayout>
#include <QTabWidget>
#include <QToolButton>
#include <QToolBar>

QTabWidget* EditorWindow::GetTabs()
{
    return tabwidget;
}

EditorWindow::EditorWindow(QWidget *parent) :
    Frame(parent)
{
    changeModeButton = new QToolButton();

    toolbar->addWidget(changeModeButton);

    tabwidget = new QTabWidget;

    mainlayout->addWidget(tabwidget, 1, 0);

    connect(changeModeButton, SIGNAL(clicked()), SIGNAL(change2SlideMode()));
}

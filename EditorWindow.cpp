#include "EditorWindow.h"
#include "EditorTab.h"
#include <QGridLayout>
#include <QTabWidget>
#include "ToolButton.h"
#include <QToolBar>

#include "TabWidget.h"

TabWidget* EditorWindow::GetTabs()
{
    return tabwidget;
}

void EditorWindow::addNewTab()
{
    EditorTab *tab = new EditorTab;
    tab->setTitle("new");
    tabwidget->addTab(tab);
}

EditorWindow::EditorWindow(QWidget *parent) :
    Frame(parent)
{
    tabwidget = new TabWidget;
    EditorTab *tab = new EditorTab;
    tab->setTitle("new");
    tabwidget->addTab(tab);

    QIcon i1(":/addtab_normal.png"), i2(":/addtab_hover.png"), i3(":/addtab_check.png");
    addTabButton = new ToolButton(i1, i2, i3);
    toolbar->addWidget(addTabButton);

    mainlayout->addWidget(tabwidget, 1, 0);

    connect(addTabButton, SIGNAL(clicked()), SLOT(addNewTab()));
}

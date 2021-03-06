#include "EditorWindow.h"
#include "EditorTab.h"
#include <QGridLayout>
#include <QTabWidget>
#include "ToolButton.h"
#include <QToolBar>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

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

void EditorWindow::compileCode()
{
    EditorTab *tab = tabwidget->tab(tabwidget->currentIndex());
    QMessageBox *box = new QMessageBox;
    if (tab->compile())
    {
        box->setText("Compile Successed!");
        tab->isCompiled = true;
    }else
    {
        box->setText("Compile Failed!");
        tab->isCompiled = false;
    }
    box->exec();
}

void EditorWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Y86 Files(*.ys *.yo)"));
    if (path.isNull() || path.isEmpty())
    {
        QMessageBox::information(NULL, "Y86 Simulator", "No file was opened!");
        return;
    }
    QMessageBox::information(NULL, "Y86 Simulator", path + " was opened!");
    QString filename = "";
    for (int i = path.size() - 1; i >= 0; --i)
        if (path[i] != '/')
            filename = path.at(i) + filename;
    else break;
    if (path[path.size() - 1] == 's')
    {
        EditorTab *tab = new EditorTab;
        tab->setTitle(filename);
        tabwidget->addTab(tab);
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        tab->setASM(stream.readAll());
        file.close();
    } else
    {

    }
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

    i1 = QIcon(":/open_normal.png"); i2 = QIcon(":/open_hover.png"); i3 = QIcon(":/open_check.png");
    openButton = new ToolButton(i1, i2, i3);

    i1 = QIcon(":/save_normal.png"); i2 = QIcon(":/save_hover.png"); i3 = QIcon(":/save_check.png");
    saveButton = new ToolButton(i1, i2, i3);

    i1 = QIcon(":/compile_normal.png"); i2 = QIcon(":/compile_hover.png"); i3 = QIcon(":/compile_check.png");
    compileButton = new ToolButton(i1, i2, i3);

    i1 = QIcon(":/sim_normal.png"); i2 = QIcon(":/sim_hover.png"); i3 = QIcon(":/sim_check.png");
    simButton = new ToolButton(i1, i2, i3);

    toolbar->addWidget(addTabButton);
    toolbar->addWidget(openButton);
    toolbar->addWidget(saveButton);
    toolbar->addWidget(compileButton);
    toolbar->addWidget(simButton);

    mainlayout->addWidget(tabwidget, 1, 0);

    connect(addTabButton, SIGNAL(clicked()), SLOT(addNewTab()));
    connect(simButton, SIGNAL(clicked()), SIGNAL(simSignal()));
    connect(compileButton, SIGNAL(clicked()), SLOT(compileCode()));
    connect(openButton, SIGNAL(clicked()), SLOT(openFile()));
}

#include "SimWidget.h"
#include "GraphView.h"
#include "MemoryTab.h"
#include "CacheTab.h"
#include "RegFileView.h"
#include <QGridLayout>
#include <QSplitter>
#include <QTabWidget>
#include <QTableWidget>
#include "Constants.h"
#include "Tools.h"
#include <QDebug>
#include <QTextStream>
#include <Pipeline.h>
#include "VAlUE.h"

void SimWidget::setup(QString asmcode, QString binary, char *mem, int max_addr)
{
    Max_Address = max_addr;
    QTextStream s1(&asmcode), s2(&binary);
    codeView->setRowCount(MAX_ADD);
    int rowcnt = 0;
    while (true)
    {
        QString t1 = s1.readLine(), t2 = s2.readLine();
        if (t1.isNull() && t2.isNull()) break;
        QTableWidgetItem *item = new QTableWidgetItem(t1);
        codeView->setItem(rowcnt, 0, item);

        item = new QTableWidgetItem(t2);
        codeView->setItem(rowcnt, 2, item);
        rowcnt++;
    }
    codeView->setRowCount(rowcnt);

    for (int i = 0; i < MAX_ADD; ++i)
        memory[i] = mem[i];

    reset();
}

void SimWidget::reset()
{
    Pipeline::reset(memory);
    graphView->reset();
    memoryTab->updateUI();
    regFileView->updateUI();
}

void SimWidget::singleStep()
{
    Pipeline::singleStep();
    graphView->updateUI();
    memoryTab->updateUI();
    regFileView->updateUI();
}

SimWidget::SimWidget(QWidget *parent) :
    QWidget(parent)
{
    graphView = new GraphView;

    memoryTab = new MemoryTab;
    cacheTab = new CacheTab;
    QTabWidget *tabwidget = new QTabWidget;
    tabwidget->addTab(memoryTab, "memory");
    tabwidget->addTab(cacheTab, "cache");

    regFileView = new RegFileView;
    codeView = new QTableWidget;
    QStringList headlist;
    headlist << "ASM" << "stage" << "binary";
    codeView->setColumnCount(3);
    codeView->setHorizontalHeaderLabels(headlist);

    QGridLayout *mainlayout = new QGridLayout;

    QSplitter *mainsplitter = new QSplitter;

    QSplitter *rightsplitter = new QSplitter;

    QSplitter *downsplitter = new QSplitter;

    downsplitter->addWidget(tabwidget);
    downsplitter->addWidget(regFileView);

    rightsplitter->setOrientation(Qt::Vertical);
    rightsplitter->addWidget(codeView);
    rightsplitter->addWidget(downsplitter);

    mainsplitter->addWidget(graphView);
    mainsplitter->addWidget(rightsplitter);

    mainlayout->addWidget(mainsplitter);

    setLayout(mainlayout);
}

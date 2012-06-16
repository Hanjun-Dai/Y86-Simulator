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
#include <QTextStream>

void SimWidget::setup(QString asmcode, QString binary, char *memory)
{
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

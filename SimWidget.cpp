#include "SimWidget.h"
#include "GraphView.h"
#include "MemoryTab.h"
#include "CacheTab.h"
#include "RegFileView.h"
#include "EditorTab.h"
#include <QGridLayout>
#include <QSplitter>
#include <QTabWidget>

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
    editorTab = new EditorTab;

    QGridLayout *mainlayout = new QGridLayout;

    QSplitter *mainsplitter = new QSplitter;

    QSplitter *rightsplitter = new QSplitter;

    QSplitter *downsplitter = new QSplitter;

    downsplitter->addWidget(tabwidget);
    downsplitter->addWidget(regFileView);

    rightsplitter->setOrientation(Qt::Vertical);
    rightsplitter->addWidget(editorTab);
    rightsplitter->addWidget(downsplitter);

    mainsplitter->addWidget(graphView);
    mainsplitter->addWidget(rightsplitter);

    mainlayout->addWidget(mainsplitter);

    setLayout(mainlayout);
}

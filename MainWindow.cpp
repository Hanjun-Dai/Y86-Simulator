#include "MainWindow.h"
#include "EditorWindow.h"
#include "SimWindow.h"
#include "PictureFlow.h"
#include "TabWidget.h"
#include <QDebug>
#include <EditorTab.h>
#include "SimWidget.h"
#include <QMessageBox>

void MainWindow::showSlideMode()
{
    if (editorWindow->GetTabs()->tabCount() <= 0) return;
    pictureFlow->clear();
    for (int i = 0; i < editorWindow->GetTabs()->tabCount(); i++)
    {
        EditorTab *tab = editorWindow->GetTabs()->tab(i);
        pictureFlow->addSlide(tab->renderImage(), tab->title());
    }

    int height = size().height() / 2;
    int width = height * pictureFlow->slide(0).width() / pictureFlow->slide(0).height();
    pictureFlow->setSlideSize(QSize(width, height));
    pictureFlow->showSlide(editorWindow->GetTabs()->tabCount() / 2);

    setCurrentWidget(pictureFlow);
}

void MainWindow::showTabMode(int index)
{
    setCurrentWidget(editorWindow);
    if (index >= 0)
        editorWindow->GetTabs()->setCurrentIndex(index);
}

void MainWindow::showSimMode()
{
    EditorTab *tab = editorWindow->GetTabs()->tab(editorWindow->GetTabs()->currentIndex());
    if (!tab->isCompiled)
    {
       QMessageBox *box = new QMessageBox;
       box->setText("This code has not been compiled yet. Please compile it first.");
       box->exec();
       return;
    }
    setCurrentWidget(simWindow);
    simWindow->getWidget()->setup(tab->getASM(), tab->getBinary(), tab->getMemory(), tab->getMaxAddr());
}

MainWindow::MainWindow(QWidget *parent) :
    QStackedWidget(parent)
{
    editorWindow = new EditorWindow;
    simWindow = new SimWindow;
    pictureFlow = new PictureFlow;

    addWidget(editorWindow);
    addWidget(simWindow);
    addWidget(pictureFlow);

    connect(editorWindow->GetTabs(), SIGNAL(change2SlideMode()), SLOT(showSlideMode()));
    connect(pictureFlow, SIGNAL(widgetSelected(int)), SLOT(showTabMode(int)));
    connect(editorWindow, SIGNAL(simSignal()), SLOT(showSimMode()));
    connect(simWindow, SIGNAL(editCode()), SLOT(showTabMode()));
}

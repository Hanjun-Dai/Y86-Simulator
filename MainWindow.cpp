#include "MainWindow.h"
#include "EditorWindow.h"
#include "SimWindow.h"
#include "PictureFlow.h"
#include <QTabWidget>
#include <EditorTab.h>

void MainWindow::showSlideMode()
{
    if (editorWindow->GetTabs()->count() <= 0) return;
    pictureFlow->clear();
    for (int i = 0; i < editorWindow->GetTabs()->count(); i++)
    {
        EditorTab *tab = reinterpret_cast<EditorTab *>(editorWindow->GetTabs()->widget(i));
        pictureFlow->addSlide(tab->renderImage(), tab->title());
    }

    int height = size().height() / 2;
    int width = height * pictureFlow->slide(0).width() / pictureFlow->slide(0).height();
    pictureFlow->setSlideSize(QSize(width, height));
    pictureFlow->showSlide(editorWindow->GetTabs()->count() / 2);

    setCurrentWidget(pictureFlow);
}

void MainWindow::showTabMode(int index)
{
    setCurrentWidget(editorWindow);
    if (index >= 0)
        editorWindow->GetTabs()->setCurrentIndex(index);
}

MainWindow::MainWindow(QWidget *parent) :
    QStackedWidget(parent)
{
    editorWindow = new EditorWindow;
    simWindow = new SimWindow;
    pictureFlow = new PictureFlow;
addWidget(simWindow);
    addWidget(editorWindow);

    addWidget(pictureFlow);

    connect(editorWindow, SIGNAL(change2SlideMode()), SLOT(showSlideMode()));
    connect(pictureFlow, SIGNAL(widgetSelected(int)), SLOT(showTabMode(int)));
}

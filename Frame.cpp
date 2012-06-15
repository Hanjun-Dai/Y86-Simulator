#include "Frame.h"
#include <QToolBar>
#include <QGridLayout>

Frame::Frame(QWidget *parent) :
    QWidget(parent)
{
    toolbar = new QToolBar;

    mainlayout = new QGridLayout;

    mainlayout->addWidget(toolbar, 0, 0);

    setLayout(mainlayout);
}

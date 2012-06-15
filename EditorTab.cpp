#include <QIcon>
#include "EditorTab.h"

class EditorTabPrivate
{
public:
    QIcon icon;
    QString title;
};

EditorTab::EditorTab(QWidget *parent)
    : QWidget(parent)
{
    d = new EditorTabPrivate();
}

EditorTab::~EditorTab()
{
    delete d;
}

QIcon EditorTab::icon() const
{
    return d->icon;
}

void EditorTab::setIcon(const QIcon &icon)
{
    d->icon = icon;
    emit iconChanged();
}

QString EditorTab::title() const
{
    return d->title;
}

void EditorTab::setTitle(const QString &title)
{
    d->title = title;
    emit titleChanged();
}

QImage EditorTab::renderImage()
{
    QImage image(size(), QImage::Format_RGB32);
    render(&image, QPoint(0, 0), QRegion(0, 0, size().width(), size().height()));
    return image;
}

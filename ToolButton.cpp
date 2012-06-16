#include "ToolButton.h"
#include <QAction>

void ToolButton::enterEvent(QEvent *e)
{
        isInside = true;
        if (!isChecked())
                setIcon(hoverIcon);
}

void ToolButton::leaveEvent(QEvent *e)
{
        isInside = false;
        if (!isChecked())
                setIcon(normalIcon);
}

void ToolButton::mousePressEvent(QMouseEvent *e)
{
        QToolButton::mousePressEvent(e);
        setIcon(checkIcon);
}

void ToolButton::mouseReleaseEvent(QMouseEvent *e)
{
        QToolButton::mouseReleaseEvent(e);
        if (!isChecked())
                setIcon(normalIcon);
}

void ToolButton::changeState(bool checked)
{
        if (checked)
                setIcon(checkIcon);
        else if (!isInside) setIcon(normalIcon);
        else setIcon(hoverIcon);
}

ToolButton::ToolButton(const QIcon &normalIcon, const QIcon &hoverIcon, const QIcon &checkIcon, QWidget *parent)
        : QToolButton(parent)
{
        this->normalIcon = normalIcon;
        this->hoverIcon = hoverIcon;
        this->checkIcon = checkIcon;
        isInside = false;
        setIcon(normalIcon);
        connect(this, SIGNAL(toggled(bool)), this, SLOT(changeState(bool)));
}

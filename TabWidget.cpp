#include "TabWidget.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPainter>
#include <QPushButton>
#include <QStackedWidget>
#include <QStyle>
#include <QGridLayout>
#include <QStyleOption>
#include <QTabBar>
#include <QDebug>

#include "ToolButton.h"
#include "EditorTab.h"

CloseButton::CloseButton(QWidget *parent)
    : QAbstractButton(parent)
{
    setFocusPolicy(Qt::NoFocus);
    setCursor(Qt::ArrowCursor);
    setToolTip(tr("Close Tab"));
    resize(sizeHint());
}

QSize CloseButton::sizeHint() const
{
    ensurePolished();
    int width = style()->pixelMetric(QStyle::PM_TabCloseIndicatorWidth, 0, this);
    int height = style()->pixelMetric(QStyle::PM_TabCloseIndicatorHeight, 0, this);
    return QSize(width, height);
}

void CloseButton::enterEvent(QEvent *event)
{
    if (isEnabled())
        update();
    QAbstractButton::enterEvent(event);
}

void CloseButton::leaveEvent(QEvent *event)
{
    if (isEnabled())
        update();
    QAbstractButton::leaveEvent(event);
}

void CloseButton::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QStyleOption opt;
    opt.init(this);
    opt.state |= QStyle::State_AutoRaise;
    if (isEnabled() && underMouse() && !isChecked() && !isDown())
        opt.state |= QStyle::State_Raised;
    if (isChecked())
        opt.state |= QStyle::State_On;
    if (isDown())
        opt.state |= QStyle::State_Sunken;

    if (const QTabBar *tb = qobject_cast<const QTabBar *>(parent()))
    {
        int index = tb->currentIndex();
        QTabBar::ButtonPosition position = (QTabBar::ButtonPosition)style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition, 0, tb);
        if (tb->tabButton(index, position) == this)
            opt.state |= QStyle::State_Selected;
    }

    style()->drawPrimitive(QStyle::PE_IndicatorTabClose, &opt, &p, this);
}

QWidget *TabWidget::currentWidget() const
{
    return stackWidget->currentWidget();
}

int TabWidget::currentIndex()
{
        return tabBar->currentIndex();
}

int TabWidget::tabCount() const
{
        return stackWidget->count();
}

EditorTab *TabWidget::tab(int index) const
{
    return reinterpret_cast<EditorTab *>(stackWidget->widget(index));
}

void TabWidget::tabIconChanged()
{
    for (int i = 0; i < stackWidget->count(); i++)
        if (sender() == stackWidget->widget(i))
        {
            tabBar->setTabIcon(i, reinterpret_cast<EditorTab *>(sender())->icon());
            return;
        }
}

void TabWidget::tabTitleChanged()
{
    for (int i = 0; i < stackWidget->count(); i++)
        if (sender() == stackWidget->widget(i))
        {
            tabBar->setTabText(i, reinterpret_cast<EditorTab *>(sender())->title());
            return;
        }
}

void TabWidget::tabMoved(int from, int to)
{
    QWidget *widget = stackWidget->widget(from);
    stackWidget->removeWidget(widget);
    stackWidget->insertWidget(to, widget);
}

void TabWidget::setCurrentIndex(int index)
{
    if (index >= 0 && index < tabBar->count())
    {
        tabBar->setCurrentIndex(index);
        stackWidget->setCurrentIndex(index);
    }
}

void TabWidget::addTab(EditorTab *page, bool isClosable)
{
    stackWidget->addWidget(page);
    connect(page, SIGNAL(iconChanged()), SLOT(tabIconChanged()));
    connect(page, SIGNAL(titleChanged()), SLOT(tabTitleChanged()));
    tabBar->addTab(page->title());
    tabBar->setCurrentIndex(tabBar->count() - 1);

    if (isClosable)
    {
        QAbstractButton *closeButton = new CloseButton(this);
        tabBar->setTabButton(tabBar->count() - 1, static_cast<QTabBar::ButtonPosition>(style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition)), closeButton);
        connect(closeButton, SIGNAL(clicked()), SLOT(closeTab()));
    }
}

void TabWidget::closeTab()
{
    if (tabBar->count() == 1)
    {
        tabBar->setTabText(0, "new");
        QWidget *page = stackWidget->widget(0);
        stackWidget->removeWidget(page);
        delete page;
        EditorTab *tab = new EditorTab;
        tab->setTitle("new");
        stackWidget->addWidget(tab);
        return;
    }
    for (int i = 0; i < tabBar->count(); ++i)
        if (tabBar->tabButton(i, static_cast<QTabBar::ButtonPosition>(style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition))) == sender())
        {
            tabBar->removeTab(i);
            QWidget *page = stackWidget->widget(i);
            stackWidget->removeWidget(page);
            delete page;
            return;
        }
}

TabWidget::TabWidget(QWidget *parent)
        : QWidget(parent)
{
    tabBar = new QTabBar();
    tabBar->setMovable(true);

    QIcon i1 = QIcon(":/tab_normal.png"), i2 = QIcon(":/tab_hover.png"), i3 = QIcon(":/tab_check.png");
    slideModeButton = new ToolButton(i1, i2, i3);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(slideModeButton);
    hlayout->addWidget(tabBar);
    hlayout->addStretch(10);

    stackWidget = new QStackedWidget();

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addLayout(hlayout, 0, 0, 1, 1);
    gridLayout->addWidget(stackWidget, 1, 0, 2, 1);

    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setSpacing(0);
    setLayout(gridLayout);

    connect(tabBar, SIGNAL(currentChanged(int)), stackWidget, SLOT(setCurrentIndex(int)));
    connect(tabBar, SIGNAL(tabMoved(int,int)), SLOT(tabMoved(int,int)));

    connect(slideModeButton, SIGNAL(clicked()), SIGNAL(change2SlideMode()));
}

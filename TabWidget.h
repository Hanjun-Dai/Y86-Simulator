#ifndef MAINTAB_H
#define MAINTAB_H

#include <QAbstractButton>
#include <QWidget>

class QPushButton;
class QStackedWidget;
class QTabBar;
class ToolButton;
class QToolButton;
class EditorTab;
class TabWidget: public QWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = 0);

    QWidget *currentWidget() const;
    void addTab(EditorTab *page, bool isClosable = true);
    int tabCount() const;
    EditorTab *tab(int index) const;
    void setCurrentIndex(int index);
    int currentIndex();

signals:
    void addTab();
    void change2SlideMode();

private slots:
    void closeTab();
    void tabIconChanged();
    void tabTitleChanged();
    void tabMoved(int from, int to);

private:
    QTabBar *tabBar;
    QStackedWidget *stackWidget;
    ToolButton *slideModeButton;
};

class CloseButton: public QAbstractButton
{
    Q_OBJECT

public:
    explicit CloseButton(QWidget *parent = 0);

    virtual QSize sizeHint() const;
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void paintEvent(QPaintEvent *event);
};

#endif

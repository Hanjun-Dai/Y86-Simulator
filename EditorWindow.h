#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <Frame.h>

class QTabWidget;
class ToolButton;
class TabWidget;
class EditorWindow : public Frame
{
    Q_OBJECT
public:
    explicit EditorWindow(QWidget *parent = 0);
    
    TabWidget* GetTabs();

public slots:

private slots:
    void addNewTab();
private:
    TabWidget *tabwidget;
    ToolButton *addTabButton;
};

#endif // EDITORWINDOW_H

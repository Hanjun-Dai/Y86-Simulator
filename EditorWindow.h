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

signals:
    void simSignal();

public slots:

private slots:
    void addNewTab();
    void compileCode();

private:
    TabWidget *tabwidget;
    ToolButton *addTabButton, *saveButton, *openButton, *compileButton, *simButton;
};

#endif // EDITORWINDOW_H

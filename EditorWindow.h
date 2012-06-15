#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <Frame.h>

class QTabWidget;
class QToolButton;
class EditorWindow : public Frame
{
    Q_OBJECT
public:
    explicit EditorWindow(QWidget *parent = 0);
    
    QTabWidget* GetTabs();

signals:
    void change2SlideMode();

public slots:

private:
    QTabWidget *tabwidget;
    QToolButton *changeModeButton;
};

#endif // EDITORWINDOW_H

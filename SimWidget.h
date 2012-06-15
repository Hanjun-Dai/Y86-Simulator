#ifndef SIMWIDGET_H
#define SIMWIDGET_H

#include <QWidget>

class GraphView;
class MemoryTab;
class CacheTab;
class RegFileView;
class EditorTab;
class SimWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SimWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
    GraphView *graphView;
    MemoryTab *memoryTab;
    CacheTab *cacheTab;
    RegFileView *regFileView;
    EditorTab *editorTab;
};

#endif // SIMWIDGET_H

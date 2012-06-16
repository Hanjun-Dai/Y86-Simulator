#ifndef SIMWIDGET_H
#define SIMWIDGET_H

#include <QWidget>

class GraphView;
class MemoryTab;
class CacheTab;
class RegFileView;
class QTableWidget;
class SimWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SimWidget(QWidget *parent = 0);
    void setup(QString asmcode, QString binary, char* memory);

signals:
    
public slots:
    
private:
    GraphView *graphView;
    MemoryTab *memoryTab;
    CacheTab *cacheTab;
    RegFileView *regFileView;
    QTableWidget *codeView;
};

#endif // SIMWIDGET_H

#ifndef SIMWIDGET_H
#define SIMWIDGET_H

#include <QWidget>
#include "Constants.h"

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
    void setup(QString asmcode, QString binary, char* mem, int max_addr);

signals:
    
public slots:
    void reset();
    void singleStep();

private:
    GraphView *graphView;
    MemoryTab *memoryTab;
    CacheTab *cacheTab;
    RegFileView *regFileView;
    QTableWidget *codeView;
    char memory[MAX_ADD + 100];
};

#endif // SIMWIDGET_H

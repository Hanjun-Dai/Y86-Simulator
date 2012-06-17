#ifndef MEMORYTAB_H
#define MEMORYTAB_H

#include <QWidget>

class QTableWidget;
class MemoryTab : public QWidget
{
    Q_OBJECT
public:
    explicit MemoryTab(QWidget *parent = 0);
    void updateUI();

signals:
    
public slots:

private:
    void setMem();
    QTableWidget* memtable;
};

#endif // MEMORYTAB_H

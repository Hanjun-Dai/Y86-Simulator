#include "MemoryTab.h"
#include <QTableWidget>
#include <QGridLayout>
#include "VAlUE.h"
#include "Tools.h"

void MemoryTab::updateUI()
{
    setMem();
}

void MemoryTab::setMem()
{
    QStringList list;
    for (int i = 0; i < MAX_ADD; i += 4)
    {
        QString label = Tools::dec2hex(i, 3);
        list << label;
        QTableWidgetItem *item;
        int value = v_memory[i];
        label = Tools::string2hex(Tools::dec2hex(value, 8)).remove(2, 6);
        item = new QTableWidgetItem(label);
        memtable->setItem(i / 4, 0, item);

        value = v_memory[i + 1];
        label = Tools::string2hex(Tools::dec2hex(value, 8)).remove(2, 6);
        item = new QTableWidgetItem(label);
        memtable->setItem(i / 4, 1, item);

        value = v_memory[i + 2];
        label = Tools::string2hex(Tools::dec2hex(value, 8)).remove(2, 6);
        item = new QTableWidgetItem(label);
        memtable->setItem(i / 4, 2, item);

        value = v_memory[i + 3];
        label = Tools::string2hex(Tools::dec2hex(value, 8)).remove(2, 6);
        item = new QTableWidgetItem(label);
        memtable->setItem(i / 4, 3, item);
    }
    memtable->setVerticalHeaderLabels(list);
}

MemoryTab::MemoryTab(QWidget *parent) :
    QWidget(parent)
{
    memtable = new QTableWidget;
    memtable->setRowCount((MAX_ADD / 4) + (MAX_ADD % 4 != 0));
    memtable->setColumnCount(4);

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(memtable);

    setLayout(layout);
}

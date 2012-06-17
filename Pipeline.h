#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>
#include "Constants.h"

class Pipeline : public QObject
{
    Q_OBJECT
public:
    static void reset(char* mem);
    static void singleStep();

signals:

public slots:

private:
    static void WriteBack();
    static void Memory();
    static void Excute();
    static void Decode();
    static void Fetch();
};

#endif // PIPELINE_H

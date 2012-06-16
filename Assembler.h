#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <QObject>

class Assembler : public QObject
{
    Q_OBJECT
public:
    explicit Assembler(QObject *parent = 0);
    static QString Compile(QString asmcode, char* binary, const int arrlen);

signals:
    
public slots:
    
};

#endif // ASSEMBLER_H

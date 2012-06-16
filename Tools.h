#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>

class Tools : public QObject
{
    Q_OBJECT
public:
    explicit Tools(QObject *parent = 0);
    static QString dec2hex(int value, int len);
    static int hex2dec(QString code);
    static QString code_asm2binary(QString code);
    static QString string2hex(QString code);
    static void setMem(int &curIndex, char* memory, QString code);
    static int getRegCode(QString code);

signals:

public slots:

private:

};

#endif // TOOLS_H

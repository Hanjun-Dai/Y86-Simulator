#include "Assembler.h"
#include <QTextStream>
#include "Constants.h"
#include "Tools.h"
#include <QMap>
#include <QDebug>

QString Assembler::Compile(QString asmcode, char *binary, const int arrlen, int &max_addr)
{
    max_addr = 0;
    QString tmp = "";
    for (int i = 0; i < asmcode.size(); ++i)
    {
        if (asmcode[i] == ',')
            tmp = tmp + " ";
        tmp = tmp + asmcode.at(i);
        if (asmcode[i] == ',')
            tmp = tmp + " ";
    }
    asmcode = tmp;
    QString unknowns[arrlen];
    for (int i = 0; i < arrlen; ++i)
    {
        binary[i] = 0;
        unknowns[i] = "";
    }

    QMap<QString, int> labels;
    labels.clear();

    QTextStream stream(&asmcode);
    QString result = "";
    bool isInComment = false;
    int curIndex = 0;
    do
    {
        QString singleLine = stream.readLine();
        if (singleLine.isNull()) break;
        QTextStream line(&singleLine);
        QString word;
        QString bcode = "";
        do
        {
            line >> word;
            if (word.isNull()) break;
            if (word == single_comm_char) break;
            if (word == multi_comm_begin) isInComment = true;
            if (word == multi_comm_end) isInComment = false;
            if (isInComment) continue;

            if (word[0] == '.')
            {
                if (word == ".pos")
                {
                    int value; line >> value;
                    curIndex = value;
                    bcode = Tools::dec2hex(value, 3) + ":";
                }
                if (word == ".align")
                {
                    int value; line >> value;
                    while (curIndex % value != 0)
                        curIndex++;
                    bcode = Tools::dec2hex(curIndex, 3) + ":";
                }
                if (word == ".long")
                {
                    line >> word;
                    word = Tools::string2hex(word);
                    bcode = Tools::dec2hex(curIndex, 3) + ": " + word;
                    Tools::setMem(curIndex, binary, word);
                }
                break;
            }

            if (word[word.size() - 1] == ':')
            {
                word = word.remove(word.size() - 1, 1);
                if (labels.count(word) == 0)
                    labels[word] = curIndex;
                continue;
            }
            QString code = Tools::code_asm2binary(word);
            if (code.isNull()) continue;
            if (code[0] == '0' || code[0] == '1' || code[0] == '9')
            {
                bcode = Tools::dec2hex(curIndex, 3) + ": " + code;
                binary[curIndex] = (char)Tools::hex2dec(code);
                curIndex++;
            }
            if (code[0] == '2' || code[0] == '6')
            {
                line >> word;

                int r1 = Tools::getRegCode(word);
                line >> word;
                line >> word;
                int r2 = Tools::getRegCode(word);

                bcode = Tools::dec2hex(curIndex, 3) + ": ";
                bcode = bcode + code + hexnum[r1] + hexnum[r2];
                binary[curIndex] = (char)Tools::hex2dec(code);
                binary[curIndex + 1] = (char)(r1 * 16 + r2);
                curIndex += 2;
            }
            if (code[0] == '3')
            {
                bcode = Tools::dec2hex(curIndex, 3) + ": ";
                line >> word;
                QString reg;
                line >> reg; line >> reg;
                binary[curIndex] = (char)Tools::hex2dec(code);
                int r = Tools::getRegCode(reg);
                binary[curIndex + 1] = (char)(15 * 16 + r);
                curIndex += 2;
                bcode = bcode + code + hexnum[15] + hexnum[r];
                if (word[0] == '$')
                {
                    word = word.remove(0, 1);
                    bool neg = false;
                    if (word[0] == '-')
                    {
                        neg = true; word = word.remove(0, 1);
                    }
                    int value = word.toInt();
                    if (neg) value = -value;
                    QString tmp = Tools::string2hex(Tools::dec2hex(value, 8));
                    Tools::setMem(curIndex, binary, tmp);
                    bcode = bcode + tmp;
                } else
                {
                    bcode = bcode + word;
                    unknowns[curIndex] = word;
                    curIndex += 4;
                }
            }
            if (code[0] == '4')
            {
                bcode = Tools::dec2hex(curIndex, 3) + ": ";
                QString reg;
                line >> reg;
                binary[curIndex] = (char)Tools::hex2dec(code);
                int r1 = Tools::getRegCode(reg);

                line >> word;
                line >> word;
                int l = word.indexOf('(');
                reg = word;
                word.remove(l, word.size() - l);
                int value = word.toInt();
                QString tmp = Tools::string2hex(Tools::dec2hex(value, 8));

                reg.remove(0, l + 1); reg.remove(reg.size() - 1, 1);
                int r2 = Tools::getRegCode(reg);

                binary[curIndex + 1] = (char)(r1 * 16 + r2);
                curIndex += 2;
                Tools::setMem(curIndex, binary, tmp);

                bcode = bcode + code + hexnum[r1] + hexnum[r2] + tmp;
            }
            if (code[0] == '5')
            {
                bcode = Tools::dec2hex(curIndex, 3) + ": ";
                binary[curIndex] = (char)Tools::hex2dec(code);
                line >> word;
                int l = word.indexOf('(');
                QString reg = word;
                word.remove(l, word.size() - l);
                int value = word.toInt();
                QString tmp = Tools::string2hex(Tools::dec2hex(value, 8));
                reg.remove(0, l + 1); reg.remove(reg.size() - 1, 1);
                int r2 = Tools::getRegCode(reg);

                line >> reg; line >> reg;

                int r1 = Tools::getRegCode(reg);

                binary[curIndex + 1] = (char)(r1 * 16 + r2);
                curIndex += 2;
                Tools::setMem(curIndex, binary, tmp);

                bcode = bcode + code + hexnum[r1] + hexnum[r2] + tmp;
            }
            if (code[0] == '7' || code[0] == '8')
            {
                bcode = Tools::dec2hex(curIndex, 3) + ": " + code;
                binary[curIndex] = (char)Tools::hex2dec(code);
                curIndex++;
                line >> word;
                if (word[0] == '$')
                {
                    word = word.remove(0, 1);
                    bool neg = false;
                    if (word[0] == '-')
                    {
                        neg = true; word = word.remove(0, 1);
                    }
                    int value = word.toInt();
                    if (neg) value = -value;
                    QString tmp = Tools::string2hex(Tools::dec2hex(value, 8));
                    Tools::setMem(curIndex, binary, tmp);
                    bcode = bcode + tmp;
                } else
                {
                    bcode = bcode + word;
                    unknowns[curIndex] = word;
                    curIndex += 4;
                }
            }
            if (code[0] == 'a' || code[0] == 'b')
            {
                bcode = Tools::dec2hex(curIndex, 3) + ": " + code;
                line >> word;
                int r = Tools::getRegCode(word);
                binary[curIndex] = (char)Tools::hex2dec(code);
                binary[curIndex + 1] = (char)(r * 16 + 15);
                curIndex += 2;
                bcode = bcode + hexnum[r] + hexnum[15];
            }
        } while (true);
        result = result + bcode + '\n';
    } while (true);

    max_addr = curIndex;

    for (int i = 0; i < arrlen; ++i)
        if (!unknowns[i].isNull() && unknowns[i].size() > 0)
        {
            if (labels.count(unknowns[i]) == 0) return NULL;
            int value = labels[unknowns[i]];
            QString tmp = Tools::string2hex(Tools::dec2hex(value, 8));
            int idx = i;
            Tools::setMem(idx, binary, tmp);
            result.replace(unknowns[i], tmp);
        }
    return result;
}

Assembler::Assembler(QObject *parent) :
    QObject(parent)
{
}

#include "Tools.h"
#include "Constants.h"
#include <QMap>
#include <QDebug>

QString Tools::dec2hex(int value, int len)
{
    QString ans = "";
    for (int i = 0; i < len; ++i)
    {
        ans = hexnum[value & 0xf] + ans;
        value = value >> 4;
    }
    ans = "0x" + ans;
    return ans;
}

int getDecNum(QString code, int idx)
{
    if (code[idx] == '0') return 0;
    if (code[idx] == '1') return 1;
    if (code[idx] == '2') return 2;
    if (code[idx] == '3') return 3;
    if (code[idx] == '4') return 4;
    if (code[idx] == '5') return 5;
    if (code[idx] == '6') return 6;
    if (code[idx] == '7') return 7;
    if (code[idx] == '8') return 8;
    if (code[idx] == '9') return 9;
    if (code[idx] == 'a') return 10;
    if (code[idx] == 'b') return 11;
    if (code[idx] == 'c') return 12;
    if (code[idx] == 'd') return 13;
    if (code[idx] == 'e') return 14;
    if (code[idx] == 'f') return 15;
}

int Tools::hex2dec(QString code)
{
    int ans = 0;
    for (int i = 0; i < code.size(); ++i)
        ans = ans * 16 + getDecNum(code, i);
    return ans;
}

int Tools::getRegCode(QString code)
{
    QString tmp = code;
    if (tmp == "%eax") return 0;
    if (tmp == "%ecx") return 1;
    if (tmp == "%edx") return 2;
    if (tmp == "%ebx") return 3;
    if (tmp == "%esp") return 4;
    if (tmp == "%ebp") return 5;
    if (tmp == "%esi") return 6;
    if (tmp == "%edi") return 7;
    return 15;
}

void Tools::setMem(int &curIndex, char *memory, QString code)
{
    for (int i = 0; i < code.size(); i += 2)
    {
        int tmp = getDecNum(code, i);
        tmp = tmp * 16;
        tmp = tmp + getDecNum(code, i + 1);
        memory[curIndex++] = (char)tmp;
    }
}

QString Tools::string2hex(QString code)
{
    int cur = code.size() - 1;
    QString result = "";
    for (int i = 0; i < 4; ++i)
    {
        if (cur > 2)
            result = result + code[cur - 1];
        else result = result + "0";
        if (cur > 1)
            result = result + code[cur];
        else result = result + "0";
        cur = cur - 2;
    }
    return result;
}

QString Tools::code_asm2binary(QString code)
{
    if (code == "halt") return "00";
    if (code == "nop") return "10";
    if (code == "rrmovl") return "20";
    if (code == "irmovl") return "30";
    if (code == "rmmovl") return "40";
    if (code == "mrmovl") return "50";
    if (code == "addl") return "60";
    if (code == "subl") return "61";
    if (code == "andl") return "62";
    if (code == "xorl") return "63";
    if (code == "jmp") return "70";
    if (code == "jle") return "71";
    if (code == "jl") return "72";
    if (code == "je") return "73";
    if (code == "jne") return "74";
    if (code == "jge") return "75";
    if (code == "jg") return "76";
    if (code == "cmovle") return "21";
    if (code == "cmovl") return "22";
    if (code == "cmove") return "23";
    if (code == "cmovne") return "24";
    if (code == "cmovge") return "25";
    if (code == "cmovg") return "26";
    if (code == "call") return "80";
    if (code == "ret") return "90";
    if (code == "pushl") return "a0";
    if (code == "popl") return "b0";
    return NULL;
}


Tools::Tools(QObject *parent) :
    QObject(parent)
{

}

#include "Tools.h"
#include "Constants.h"
#include <QMap>
#include <QDebug>
#include "VAlUE.h"

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

int Tools::Get4Bytes(int idx)
{
    return ((v_memory[idx + 3] & 0xFF) << 24) +
            ((v_memory[idx + 2] & 0xFF) << 16) +
            ((v_memory[idx + 1] & 0xFF) << 8) +
            (v_memory[idx] & 0xFF);
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
    if (code == "nop") return "00";
    if (code == "halt") return "10";
    if (code == "rrmovl") return "20";
    if (code == "irmovl") return "30";
    if (code == "rmmovl") return "40";
    if (code == "mrmovl") return "50";
    if (code == "addl") return "60";
    if (code == "subl") return "61";
    if (code == "andl") return "62";
    if (code == "xorl") return "63";
    if (code == "iaddl") return "31";
    if (code == "isubl") return "32";
    if (code == "iandl") return "33";
    if (code == "ixorl") return "34";
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

void Tools::ALU()
{
    if (aluFun == 0)
    {
        e_valE = aluA + aluB;
        if (set_cc)
            {
                ZF = (e_valE == 0);
                SF = (e_valE < 0);
                OF = (((aluA < 0) == (aluB < 0)) &&
                      ((e_valE < 0) != (aluA < 0)));
            }
    }

    if (aluFun == 1)
    {
        int y = ~aluB + 1;
        e_valE = aluA - aluB;
        if (set_cc)
        {
            ZF = (e_valE == 0);
            SF = (e_valE < 0);
            OF = (((aluA < 0) == (y < 0)) &&
                  ((e_valE < 0) != (aluA < 0)));
        }
    }

    if (aluFun == 2)
    {
        e_valE = aluA & aluB;
        if (set_cc)
        {
            ZF = (e_valE == 0);
            SF = (e_valE < 0);
            OF = false;
        }
    }

    if (aluFun == 3)
    {
        e_valE = aluA ^ aluB;
        if (set_cc)
        {
            ZF = (e_valE == 0);
            SF = (e_valE < 0);
            OF = false;
        }
    }
}

void Tools::SetCnd()
{
    e_Cnd = true;
    if (E_icode != IJXX) return;
    if (E_ifun == 0)
        e_Cnd = true;

    if (E_ifun == 1)
        e_Cnd = (SF ^ OF) | ZF;

    if (E_ifun == 2)
        e_Cnd = SF ^ OF;

    if (E_ifun == 3)
        e_Cnd = ZF;

    if (E_ifun == 4)
        e_Cnd = !ZF;

    if (E_ifun == 5)
        e_Cnd = !(SF ^ OF);

    if (E_ifun == 6)
        e_Cnd = (!(SF ^ OF)) & (!ZF);
}

Tools::Tools(QObject *parent) :
    QObject(parent)
{

}

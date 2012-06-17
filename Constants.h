#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

const int MAX_ADD = 2048;
const char hexnum[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
const QString single_comm_char = "#";
const QString multi_comm_begin = "/*";
const QString multi_comm_end = "*/";

//----------status---------------------
const int SAOK = 1;
const int SADR = 2;
const int SINS = 3;
const int SHLT = 4;

//----------icode----------------------
const int INOP = 0;
const int IHALT = 1;
const int IRRMOVL = 2;
const int IIRMOVL = 3;
const int IRMMOVL = 4;
const int IMRMOVL = 5;
const int IOPL = 6;
const int IJXX = 7;
const int ICALL = 8;
const int IRET = 9;
const int IPUSHL = 10;
const int IPOPL = 11;

//----------registers------------------
const int REAX = 0;
const int RECX = 1;
const int REDX = 2;
const int REBX = 3;
const int RESP = 4;
const int REBP = 5;
const int RESI = 6;
const int REDI = 7;
const int RNONE = 15;

#endif // CONSTANTS_H

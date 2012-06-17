#ifndef VALUE_H
#define VALUE_H

#include "Constants.h"

extern char v_memory[MAX_ADD + 100];
extern bool instr_valid;
extern bool imem_error;
extern int Final_stat;
extern bool halt_flag;
extern bool dmem_error;
extern int Max_Address;

//------------------condition codes---------------------------
extern bool ZF, SF, OF;

//---------------------Registers------------------------------
extern int reg[16];

//----------Pipeline register F------------------------------

extern int f_predPC;
extern int f_pc;
extern int F_predPC;
extern int f_icode;
extern int f_valC;
extern int f_valP;
extern int f_stat;
extern int f_ifun;
extern int f_rA;
extern int f_rB;

//----------Pipeline register D------------------------------
extern int D_stat;
extern int D_icode;
extern int D_ifun;
extern int D_rA;
extern int D_rB;
extern int D_valC;
extern int D_valP;
extern int d_srcA;
extern int d_srcB;
extern int d_dstE;
extern int d_dstM;
extern int d_valA;
extern int d_valB;
extern int d_stat;

//----------Pipeline register E------------------------------
extern int E_stat;
extern int E_icode;
extern int E_ifun;
extern int E_valC;
extern int E_valA;
extern int E_valB;
extern int E_dstE;
extern int E_dstM;
extern int E_srcA;
extern int E_srcB;
extern int e_dstE;
extern int e_valE;
extern int aluA;
extern int aluB;
extern int aluFun;
extern bool set_cc;
extern bool e_cmov_Cnd;
extern bool e_Cnd;
extern int e_valA;
extern int e_stat;

//----------Pipeline register M------------------------------
extern int M_stat;
extern int M_icode;
extern bool M_Cnd;
extern int M_valE;
extern int M_valA;
extern int M_dstE;
extern int M_dstM;
extern int m_valM;
extern int mem_addr;
extern bool mem_read;
extern bool mem_write;
extern int m_stat;
extern bool m_cmov_Cnd;

//----------Pipeline register W------------------------------
extern int W_stat;
extern int W_icode;
extern int W_valE;
extern int W_valM;
extern int W_dstE;
extern int W_dstM;
extern int w_stat;

//----------pipeline register control signal-----------------
extern bool F_bubble;
extern bool F_stall;

extern bool D_stall;
extern bool D_bubble;

extern bool E_stall;
extern bool E_bubble;

extern bool M_stall;
extern bool M_bubble;

#endif // VALUE_H

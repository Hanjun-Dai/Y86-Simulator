#include "VAlUE.h"

 char v_memory[MAX_ADD + 100];
 bool instr_valid;
 bool imem_error;
 int Final_stat;
 bool halt_flag;
 bool dmem_error;
 int Max_Address;

//------------------condition codes---------------------------
 bool ZF, SF, OF;

//---------------------Registers------------------------------
 int reg[16];

//----------Pipeline register F------------------------------

 int f_predPC;
 int f_pc;
 int F_predPC;
 int f_icode;
 int f_valC;
 int f_valP;
 int f_stat;
 int f_ifun;
 int f_rA;
 int f_rB;

//----------Pipeline register D------------------------------
 int D_stat;
 int D_icode;
 int D_ifun;
 int D_rA;
 int D_rB;
 int D_valC;
 int D_valP;
 int d_srcA;
 int d_srcB;
 int d_dstE;
 int d_dstM;
 int d_valA;
 int d_valB;
 int d_stat;

//----------Pipeline register E------------------------------
 int E_stat;
 int E_icode;
 int E_ifun;
 int E_valC;
 int E_valA;
 int E_valB;
 int E_dstE;
 int E_dstM;
 int E_srcA;
 int E_srcB;
 int e_dstE;
 int e_valE;
 int aluA;
 int aluB;
 int aluFun;
 bool set_cc;
 bool e_Cnd;
 int e_valA;
 int e_stat;
 bool e_cmov_Cnd;

//----------Pipeline register M------------------------------
 int M_stat;
 int M_icode;
 bool M_Cnd;
 int M_valE;
 int M_valA;
 int M_dstE;
 int M_dstM;
 int m_valM;
 int mem_addr;
 bool mem_read;
 bool mem_write;
 int m_stat;
 bool m_cmov_Cnd;

//----------Pipeline register W------------------------------
 int W_stat;
 int W_icode;
 int W_valE;
 int W_valM;
 int W_dstE;
 int W_dstM;
 int w_stat;

 //----------pipeline register control signal-----------------
 bool F_bubble;
 bool F_stall;

 bool D_stall;
 bool D_bubble;

 bool E_stall;
 bool E_bubble;

 bool M_stall;
 bool M_bubble;

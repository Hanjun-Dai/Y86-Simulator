#include "Pipeline.h"
#include "VAlUE.h"
#include "Tools.h"
#include <QMessageBox>

void Pipeline::reset(char *mem)
{
    for (int i = 0; i < MAX_ADD; ++i)
        v_memory[i] = mem[i];
    imem_error = instr_valid = dmem_error = false;
    F_predPC = 0;
    F_bubble = F_stall = D_stall = D_bubble = E_stall = E_bubble = M_stall = M_bubble = false;
    for (int i = 0; i < 16; ++i)
        reg[i] = 0;
    ZF = SF = OF = 0;

    f_predPC = f_pc = F_predPC = f_icode = f_valC = f_valP = f_stat = f_ifun = f_rA = f_rB = 0;
    D_icode = D_ifun = D_rA = D_rB = D_valC = D_valP = d_srcA = d_srcB = d_dstE = d_dstM = d_valA = d_valB = 0;
    E_icode = E_ifun = E_valC = E_valA = E_valB = E_dstE = E_dstM = E_srcA = E_srcB = e_dstE = e_valE = aluA = aluB = aluFun = set_cc = e_Cnd = e_valA = 0;
    M_icode = M_Cnd = M_valE = M_valA = M_dstE = M_dstM = m_valM = mem_addr = mem_read = mem_write = 0;
    W_icode = W_valE = W_valM = W_dstE = W_dstM = 0;
    D_stat = E_stat = M_stat = W_stat = Final_stat = SAOK;
    f_stat = d_stat = e_stat = m_stat = w_stat = SAOK;
    halt_flag = false;
    e_cmov_Cnd = true;
    m_cmov_Cnd = true;
}

void SelectPC()
{
    if (M_icode == IJXX && !M_Cnd)
    {
        f_pc = M_valA;
        return;
    }
    if (W_icode == IRET)
    {
        f_pc = W_valM;
        return;
    }
    f_pc = F_predPC;
}

void PredictPC()
{
    if (f_icode == IJXX || f_icode == ICALL)
        f_predPC = f_valC;
    else f_predPC = f_valP;
}

bool NeedReg()
{
    if (f_icode == IRRMOVL ||
        f_icode == IOPL ||
        f_icode == IPUSHL ||
        f_icode == IPOPL ||
        f_icode == IIRMOVL ||
        f_icode == IRMMOVL ||
        f_icode == IMRMOVL)
        return true;
    return false;
}

bool NeedvalC()
{
    if (f_icode == IIRMOVL ||
        f_icode == IRMMOVL ||
        f_icode == IMRMOVL ||
        f_icode == IJXX ||
        f_icode == ICALL)
        return true;
    return false;
}

void CheckInsValid()
{
    if (f_icode == INOP || f_icode == IHALT || f_icode == IRRMOVL || f_icode == IIRMOVL || f_icode == IRMMOVL
            || f_icode == IMRMOVL || f_icode == IOPL ||  f_icode == IJXX || f_icode == ICALL || f_icode == IRET
            || f_icode == IPUSHL || f_icode == IPOPL)
        instr_valid = true;
    else instr_valid = false;
}

void set_f_stat()
{
    if (imem_error)
        f_stat = SADR;
    else if (!instr_valid)
        f_stat = SINS;
    else if (f_icode == IHALT)
        f_stat = SHLT;
    else f_stat = SAOK;
}

void Pipeline::Fetch()
{
    if (halt_flag) return;
    SelectPC();

    if (f_pc < 0 || f_pc > MAX_ADD)
        imem_error = true;
    else imem_error = false;

    f_valP = f_pc;
    f_valP++;
    if (!imem_error)
    {
        f_icode = (v_memory[f_pc] & 0xf0) >> 4;
        f_ifun = v_memory[f_pc] & 0x0f;
    }

    CheckInsValid();
    set_f_stat();

    if (NeedReg())
    {
        f_valP++;
        f_rA = (v_memory[f_pc + 1] & 0xf0) >> 4;
        f_rB = v_memory[f_pc + 1] & 0x0f;
    }
    if (NeedvalC())
    {
        if (!imem_error) f_valC = Tools::Get4Bytes(f_valP);
        f_valP += 4;
    }

    PredictPC();
}

void Pipeline::Decode()
{
    //d_srcA
    if (D_icode == IRRMOVL ||
        D_icode == IRMMOVL ||
        D_icode == IOPL ||
        D_icode == IPUSHL)
        d_srcA = D_rA;
    else if (D_icode == IPOPL || D_icode == IRET)
            d_srcA = RESP;
    else d_srcA = RNONE;

    //d_srcB
    if (D_icode == IOPL ||
        D_icode == IRMMOVL ||
        D_icode == IMRMOVL)
        d_srcB = D_rB;
    else if (D_icode == IPUSHL ||
             D_icode == IPOPL ||
             D_icode == ICALL ||
             D_icode == IRET)
        d_srcB = RESP;
    else if (D_icode == IIRMOVL && D_ifun > 0)
        d_srcB = D_rB;
    else d_srcB = RNONE;

    //d_dstE
    if (D_icode == IRRMOVL ||
        D_icode == IIRMOVL ||
        D_icode == IOPL)
        d_dstE = D_rB;
    else if (D_icode == IPUSHL ||
             D_icode == IPOPL ||
             D_icode == ICALL ||
             D_icode == IRET)
            d_dstE = RESP;
    else d_dstE = RNONE;

    //d_dstM
    if (D_icode == IMRMOVL ||
        D_icode == IPOPL)
        d_dstM = D_rA;
    else d_dstM = RNONE;

    //d_valA
    if (D_icode == ICALL || D_icode == IJXX)
        d_valA = D_valP;
    else if (d_srcA == e_dstE)
        d_valA = e_valE;
    else if (d_srcA == M_dstM)
        d_valA = m_valM;
    else if (d_srcA == M_dstE)
        d_valA = M_valE;
    else if (d_srcA == W_dstM)
        d_valA = W_valM;
    else if (d_srcA == W_dstE)
        d_valA = W_valE;
    else
        d_valA = reg[d_srcA];

    //d_valB
    if (d_srcB == e_dstE)
        d_valB = e_valE;
    else if (d_srcB == M_dstM)
        d_valB = m_valM;
    else if (d_srcB == M_dstE)
        d_valB = M_valE;
    else if (d_srcB == W_dstM)
        d_valB = W_valM;
    else if (d_srcB == W_dstE)
        d_valB = W_valE;
    else d_valB = reg[d_srcB];

    d_stat = D_stat;
}

void Pipeline::Excute()
{
    if (E_icode == IHALT) halt_flag = true;
    //aluA
    if (E_icode == IRRMOVL ||
        E_icode == IOPL)
        aluA = E_valA;
    else if (E_icode == IIRMOVL ||
             E_icode == IRMMOVL ||
             E_icode == IMRMOVL)
        aluA = E_valC;
    else if (E_icode == ICALL ||
             E_icode == IPUSHL)
        aluA = -4;
    else if (E_icode == IRET ||
             E_icode == IPOPL)
        aluA = 4;

    //aluB;
    if (E_icode == IRMMOVL ||
        E_icode == IMRMOVL ||
        E_icode == IOPL ||
        E_icode == ICALL ||
        E_icode == IPUSHL ||
        E_icode == IRET ||
        E_icode == IPOPL)
        aluB = E_valB;
    else if (E_icode == IRRMOVL)
            aluB = 0;
    else if(E_icode == IIRMOVL)
    {
        if (E_ifun == 0)
            aluB = 0;
        else aluB = E_valB;
    }

    //aluFun
    if (E_icode == IOPL)
        aluFun = E_ifun;
    else if (E_icode == IIRMOVL && E_ifun > 0)
        aluFun = E_ifun - 1;
    else aluFun = 0;

    //set_cc
    set_cc = false;
    if (E_icode == IOPL)
    {
        if (m_stat == SAOK && W_stat == SAOK)
            set_cc = true;
    }

    //set_cnd_cc
    e_cmov_Cnd = true;
    if (E_icode == IRRMOVL && E_ifun > 0)
    {
        if (m_stat == SAOK && W_stat == SAOK)
        {
            if (E_ifun == 1)
                e_cmov_Cnd = (SF ^ OF) | ZF;

            if (E_ifun == 2)
                e_cmov_Cnd = SF ^ OF;

            if (E_ifun == 3)
                e_cmov_Cnd = ZF;

            if (E_ifun == 4)
                e_cmov_Cnd = !ZF;

            if (E_ifun == 5)
                e_cmov_Cnd = !(SF ^ OF);

            if (E_ifun == 6)
                e_cmov_Cnd = (!(SF ^ OF)) & (!ZF);
        }
    }

    Tools::ALU();

    Tools::SetCnd();

    e_valA = E_valA;

    if (E_icode == IRRMOVL && !e_Cnd)
        e_dstE = RNONE;
    else e_dstE = E_dstE;

    e_stat = E_stat;
}

void Pipeline::Memory()
{
    if (M_icode == IRMMOVL ||
        M_icode == IPUSHL ||
        M_icode == ICALL ||
        M_icode == IMRMOVL)
        mem_addr = M_valE;
    else if (M_icode == IPOPL ||
             M_icode == IRET)
         mem_addr = M_valA;

    if (M_icode == IMRMOVL ||
        M_icode == IPOPL ||
        M_icode == IRET)
        mem_read = true;
    else mem_read = false;

    if (M_icode == IRMMOVL ||
        M_icode == IPUSHL ||
        M_icode == ICALL)
        mem_write = true;
    else mem_write = false;

    if (mem_addr < 0 || mem_addr + 4 > MAX_ADD)
        dmem_error = true;
    else dmem_error = false;

    if (!dmem_error)
    {
        if (mem_read)
            m_valM = Tools::Get4Bytes(mem_addr);
        if (mem_write)
        {
            v_memory[mem_addr + 3] = (M_valA >> 24) & 0xFF;
            v_memory[mem_addr + 2] = (M_valA >> 16) & 0xFF;
            v_memory[mem_addr + 1] = (M_valA >> 8) & 0xFF;
            v_memory[mem_addr] = M_valA & 0xFF;
        }
    }

    if (dmem_error)
        m_stat = SADR;
    else m_stat = M_stat;

    m_cmov_Cnd = e_cmov_Cnd;
}

void Pipeline::WriteBack()
{
    w_stat = W_stat;
    if (W_icode == IRMMOVL) return;

    if (m_cmov_Cnd)
    {
        reg[W_dstE] = W_valE;
        reg[W_dstM] = W_valM;
    }
}

void control()
{
    F_bubble = false;

    if (((E_icode == IMRMOVL || E_icode == IPOPL) &&
         (E_dstM == d_srcA || E_dstM == d_srcB)) ||
         (D_icode == IRET || E_icode == IRET || M_icode == IRET))
        F_stall = true;
    else F_stall = false;

    if ((E_icode == IMRMOVL || E_icode == IPOPL) &&
        (E_dstM == d_srcA || E_dstM == d_srcB))
          D_stall = true;
    else D_stall = false;

    if ((E_icode == IJXX && !e_Cnd) ||
            (!((E_icode == IMRMOVL || E_icode == IPOPL) && (E_dstM == d_srcA || E_dstM == d_srcB)) &&
         (D_icode == IRET || E_icode == IRET || M_icode == IRET)))
          D_bubble = true;
      else D_bubble = false;

    E_stall = false;

    if ((E_icode == IJXX && !e_Cnd) ||
        ((E_icode == IMRMOVL || E_icode == IPOPL) &&
         (E_dstM == d_srcA || E_dstM == d_srcB)))
        E_bubble = true;
    else
        E_bubble = false;

    M_stall = false;
}

void update()
{
    //pipeline register W
    W_icode = M_icode;
    W_valE = M_valE;
    W_valM = m_valM;
    W_dstE = M_dstE;
    W_dstM = M_dstM;
    W_stat = m_stat;

    //pipeline register M
    M_icode = E_icode;
    M_Cnd = e_Cnd;
    M_valE = e_valE;
    M_valA = E_valA;
    M_dstE = e_dstE;
    M_dstM = E_dstM;
    M_stat = e_stat;

    //pipeline register E
    E_icode = D_icode;
    E_ifun = D_ifun;
    E_valC = D_valC;
    E_valA = d_valA;
    E_valB = d_valB;
    E_dstE = d_dstE;
    E_dstM = d_dstM;
    E_srcA = d_srcA;
    E_srcB = d_srcB;
    E_stat = d_stat;

    if (E_bubble)
    {
        E_icode = E_ifun = 0;
        E_dstE = RNONE;
        E_dstM = RNONE;
        E_srcA = RNONE;
        E_srcB = RNONE;
    }

    //pipline register D
    if (!D_stall)
    {
        D_icode = f_icode;
        D_ifun = f_ifun;
        D_rA = f_rA;
        D_rB = f_rB;
        D_valC = f_valC;
        D_valP = f_valP;
    }
    if (D_bubble)
    {
        D_icode = 0;
        D_ifun = 0;
    }

    D_stat = f_stat;

    if (!F_stall)
        F_predPC = f_predPC;

    Final_stat = w_stat;
}

void Pipeline::singleStep()
{
    if (f_pc > Max_Address + 8)
    {
        QMessageBox::information(NULL, "Y86 Simulator", "Finished!");
        return;
    }
    if (W_icode == IHALT)
    {
        Final_stat = W_stat;
        QMessageBox::information(NULL, "Y86 Simulator", "Halt!");
        return;
    }

    if (W_stat == SADR || W_stat == SINS)
    {
        if (W_stat == SADR)
            QMessageBox::information(NULL, "Y86 Simulator", "Address Error!");
        else QMessageBox::information(NULL, "Y86 Simulator", "Instruction Error!");
        return;
    }

    if (M_stat == SADR || M_stat == SINS)
    {
        if (M_stat == SADR)
            QMessageBox::information(NULL, "Y86 Simulator", "Address Error!");
        else QMessageBox::information(NULL, "Y86 Simulator", "Instruction Error!");
        return;
    }
    WriteBack();
    Memory();
    Excute();
    Decode();
    Fetch();

    control();

    update();
}

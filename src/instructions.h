#ifndef INSTR_H
#define INSTR_H

#include "cpu.h"
#include <stdio.h>

#define UPPER(x) (x >> 4)
#define LOWER(x) (x & 0x0F)

#define COMB_REGS(r1, r2) (r1 << 4 | r2)
#define NOP(pc) (pc++)


U16 LD_reg_x16(U16 r, U16 x); 
U8 LD_reg_x8(U8 r, U8 x);
U16 LD_x16_reg(U16 x, U16 r); 
U16 LDD_reg_x16(U16 r, U16 x); //decrement mnemonic 
U16 LDI_reg_x16(U16 r, U16 x); //increment mnemonic


#endif


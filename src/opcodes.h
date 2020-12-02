#ifndef INSTR_H
#define INSTR_H

#include "cpu.h"


#define UPPER(x) (x >> 4)
#define LOWER(x) (x & 0x0F)

#define NOP(pc) (pc++)

U16 combine_regs(U8 r1, U8 r2);

void ld_r16_n16(U16 r, U16 n);
void ld_r16_n8(U16 r,  U8 n);
void ld_r8_n8(U8 r, U8 n);
void ldi_r16_n8(U16 r, U8 n); 
void ldd_r16_n8(U16 r, U8 n); 

void inc_regs(U16 reg);
void dec_regs(U16 reg);

#endif


#ifndef INSTR_H
#define INSTR_H

#include "cpu.h"


#define UPPER(x) (x >> 4)
#define LOWER(x) (x & 0x0F)

#define COMB_REGS(r1, r2) (r1 << 4 | r2)
#define NOP(pc) (pc++)

void ld_r16_n16(U16 r, U16 n);
void ld_r16_n8(U16 r,  U8 n);
void ld_r8_n8(U8 r, U8 n);
void ldi_r16_n8(U16 r, U8 n); 
void ldd_r16_n8(U16 r, U8 n); 

void inc_regs(U16 reg);

#endif


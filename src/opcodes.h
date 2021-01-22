#ifndef INSTR_H
#define INSTR_H

#include "cpu.h"

#define UPPER(x) (x >> 4)
#define LOWER(x) (x & 0x0F)
#define NOP(pc) (pc++)

#define STOP(pc) (pc = 0)

u16 combine_regs(u8 r1, u8 r2);

u16 ld_r16_n16(u16 r, u16 n);
u16 ld_r16_n8(u16 r,  u8 n);
u8 ld_r8_n8(u8 r, u8 n);
u8 ld_r8_n16(u8 r, u16 n);
u16 ldi_r16_n8(u16 r, u8 n); 
u16 ldd_r16_n8(u16 r, u8 n); 

u16 inc_reg(u16 reg);
u16 dec_reg(u16 reg);

void rlca(u8 a, u8 carry);
void rrca(u8 a, u8 carry_flag);

u16 add(u16 x, u16 y);
u16 sub(u16 x, u16 y);

#endif


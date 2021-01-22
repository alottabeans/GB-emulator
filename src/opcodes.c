#include "opcodes.h"
#include <stdio.h>


u16 combine_regs(u8 r1, u8 r2)
{
  u16 res;
  
  res = r1 << 4 | r2;

  return res;
}

u16 ld_r16_n16(u16 r, u16 n)
{
  r = n;
  return r;
}

u16 ld_r16_n8(u16 r, u8 n)
{
  r = n;
  return r;
}

u8 ld_r8_n8(u8 r, u8 n)
{
  r = n;
  return r;
}

u8 ld_r8_n16(u8 r, u16 n)
{
  r = n;
  return r;
}

u16 ldi_r16_n8(u16 r, u8 n)
{
  r++;
  r = n;
  return r;
}

u16 ldd_r16_n8(u16 r, u8 n)
{
  r--;
  r = n;

  return r;
}

u16 inc_reg(u16 reg)
{
  reg++;
  return reg;
}

u16 dec_reg(u16 reg)
{
  reg--;
  return reg;
}

//7th bit of a is copied into the carry flag and into 0th bit of a
void rlca(u8 a, u8 carry_flag)
{
  u8 seventh_bit = (a & (1 << 7)) >> 7;
  u8 zero_bit = (a & (1 << 0)) >> 0;
  
  zero_bit = seventh_bit;
  carry_flag = seventh_bit;
}

//the 0th bit of a is copied into the carry flag and into 7th bit of a
void rrca(u8 a, u8 carry_flag){
  u8 zero_bit = (a & (a << 0)) >> 0;
  u8 seventh_bit = (a & (a << 7)) >> 7;
  
  carry_flag = zero_bit;
  seventh_bit = zero_bit;
}


u16 add(u16 x, u16 y)
{
  u16 res = x + y;
  return res; 
}

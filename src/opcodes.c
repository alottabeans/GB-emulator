#include "opcodes.h"
#include <stdio.h>

void ld_r16_n16(U16 r, U16 n)
{
  r = n;
}

void ld_r16_n8(U16 r,  U8 n)
{
  r = n;
}

void ld_r8_n8(U8 r, U8 n)
{
  r = n;
}

void ldi_r16_n8(U16 r, U8 n)
{
  r++;
  r = n;
}

void ldd_r16_n8(U16 r, U8 n)
{
  r--;
  r = n;
}

void inc_regs(U16 regs)
{
  regs++;
}

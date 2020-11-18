#include <stdio.h>
#include "instructions.h"
 

U16 LD_reg_x16(U16 r, U16 x)
{
  U8 rhigh, rlow; 
  U8 xhigh, xlow; 

  rhigh = UPPER(r);
  rlow = LOWER(r);
  
  xhigh = UPPER(x);
  xlow = LOWER(x);    

  rhigh = xhigh;
  rlow = xlow;

  U16 _reg = COMB_REGS(rhigh, rlow);

  return _reg;
}

U16 LD_x16_reg(U16 x, U16 r)
{
  U8 xhigh, xlow;
  U8 rhigh, rlow;

  xhigh = UPPER(x);
  xlow = LOWER(x);

  rhigh = UPPER(r);
  rlow = LOWER(r);

  xhigh = rhigh;
  xlow = rlow;

  U16 _x = COMB_REGS(xhigh, xlow);

  return _x;
}


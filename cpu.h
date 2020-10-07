#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef uint8_t U8;
typedef uint16_t U16;

struct GB
{
  U16 Mem[0xFFFF];
  int display[160 * 144];

  U16 op;

  U8 a;   
  U8 b;   
  U8 c;
  U8 d;
  U8 e;
  U8 f;
  U8 h;   
  U8 l;   
    
  U16 SP; //stack pointer
  U16 PC; //program counter  
};

void init_gb(struct GB *gb);
void load_rom(struct GB *gb);
U16 fetch_opcode(struct GB *gb);
U16 execute_opcode(struct GB *gb);

void get_state(struct GB *gb);

#endif

#ifndef CPU_H
#define CPU_H
 
#include <stdint.h>

typedef uint8_t U8;
typedef uint16_t U16;

struct CPU
{
  U16 Mem[0xFFFF];
  int display[160 * 144];

  U8 a;
  U8 f;
  U8 b;
  U8 d;
  U8 e;
  U8 h;
  U8 l;
  
  U16 SP; 
  U16 PC; 
};

void init_gb(struct CPU *cpu);
void load_rom(struct CPU *cpu);
U8 read_opcodes(struct CPU *cpu);
U16 combine_regs(U8 r1, U8 r2); 
void execute_opcodes(struct CPU *cpu);

#endif

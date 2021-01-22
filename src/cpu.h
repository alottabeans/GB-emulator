#ifndef CPU_H
#define CPU_H
 
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;


struct CPU
{
  u16 Mem[0xFFFF];

  int display[160 * 144];

  u8 a;
  u8 f;
  u8 b;
  u8 c;
  u8 d;
  u8 e;
  u8 h;
  u8 l;

  u16 SP; 
  u16 PC; 
};

struct Flags
{
  u8 z;
  u8 n;
  u8 h;
  u8 c;
};

void init_gb(struct CPU *cpu);
void load_rom(struct CPU *cpu);
u8 fetch_opcodes(struct CPU *cpu);
void execute_opcodes(struct CPU *cpu);
void print_regs(struct CPU *cpu);


#endif

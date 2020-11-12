#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "instructions.h"


void init_cpu(struct CPU *cpu)
{ 
  cpu->SP = 0;
  cpu->PC = 0x0100; 
} 

void load_rom(struct CPU *cpu)
{
  FILE *rom;
  
  rom = fopen("../roms/Dr. Mario (JU) (V1.1).gb", "rb");
  
  if(rom == NULL)
    {
      printf("File was not found\n");
      fclose(rom);
    }

  
  fread(&cpu->Mem[cpu->PC], 1, 0xFFFF, rom); 
  fclose(rom);
}
 

U16 read_opcode(struct CPU *cpu)
{  
  U16 ret;
 
  ret = cpu->Mem[cpu->PC >> 8] | cpu->Mem[cpu->PC];

  cpu->PC += 1;

  return ret;
}


U16 combine_regs(U8 r1, U8 r2)
{
  U16 ret;

  ret = r1 | r2;
  
  return ret;
}

void execute_opcodes(struct CPU *cpu)
{
  U8 upper, lower;
  
  U16 current_op = read_opcode(cpu);
  
  U8 op_queue[2] = {upper, lower};

  upper = current_op & 0x00FF;
  lower = current_op >> 8;
  
  for(int i=0; i < 2; i++)
    {
      U8 current_op = op_queue[i];

      printf("current_op: 0x%X\n", current_op);

      switch(current_op)
	{  
	case 0x0: NOP(cpu->PC); break;
	case 0x1: LD_bc_u16(combine_regs(cpu->b, cpu->c), ); break;
	case 0x2: break;
	  
	//default: printf("Opcode 0x%X not found!", current_op); exit(0);
	}
    }
}



int main(void)
{
  struct CPU cpu;
  
  init_cpu(&cpu);
  load_rom(&cpu);

  for(int i=0; i < 30; i++)
    {
      execute_opcodes(&cpu);
    }

  return 0;
}


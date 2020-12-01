#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "opcodes.h"
#include "util.h"

void init_cpu(struct CPU *cpu)
{ 
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


U16 fetch_opcode(struct CPU *cpu)
{  
  U16 ret;

  ret = cpu->Mem[cpu->PC >> 8] | cpu->Mem[cpu->PC];
  
  cpu->PC += 1;
  
  return ret;
}

void execute_opcodes(struct CPU *cpu)
{   
  U8 upper, lower;
  
  U16 current_op = fetch_opcode(cpu);
  
  upper = current_op & 0x00FF;
  lower = current_op >> 8;

  U8 op_queue[2] = {upper , lower};
  //current_op = upper << 8 | lower;
  
  
  printf("current_op : 0x%X\n", current_op);

  for(int i=0; i < 2; i++)
    {
      current_op = op_queue[i];

      switch(current_op)
	{  
	case 0x0:
	  NOP(cpu->PC);
	  break;      
    
	case 0x1:
	  ld_r16_n16(COMB_REGS(cpu->b, cpu->c), cpu->Mem[cpu->PC + 2]);
	  cpu->PC += 3;
	  break;
      
	case 0x2:
	  ld_r16_n8(COMB_REGS(cpu->Mem[cpu->b], cpu->Mem[cpu->c]), cpu->a); 
	  cpu->PC++;
	  break;

	case 0x3:
	  inc_regs(COMB_REGS(cpu->b, cpu->c));
	  cpu->PC++; 
	  break;
      
	default: printf("Unsupported Opcode 0x%X\n", current_op); NOP(cpu->PC);
	}
    }
}

void print_regs(struct CPU *cpu)
{
  printf("reg a : 0x%X\n", cpu->a);
  printf("reg f : 0x%X\n", cpu->f);
  printf("reg b : 0x%X\n", cpu->b);
  printf("reg c : 0x%X\n", cpu->c);
  printf("reg d : 0x%X\n", cpu->d);
  printf("reg e : 0x%X\n", cpu->e);
  printf("reg h : 0x%X\n", cpu->h);
  printf("reg l : 0x%X\n", cpu->l);
  
  printf("reg AF : 0x%X\n", COMB_REGS(cpu->a, cpu->f));
  printf("reg BC : 0x%X\n", COMB_REGS(cpu->b, cpu->c));
  printf("reg DE : 0x%X\n", COMB_REGS(cpu->d, cpu->e));
  printf("reg HL : 0x%X\n", COMB_REGS(cpu->h, cpu->l));
}


int main(void)
{
  struct CPU cpu;
  
  init_cpu(&cpu);
  load_rom(&cpu);

  for(int i=0; i < 10; i++)
    {
      //print_regs(&cpu);
      execute_opcodes(&cpu);
    }

  return 0;
}


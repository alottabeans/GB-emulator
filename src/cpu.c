#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "instructions.h"
 

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

U16 read_opcode(struct CPU *cpu)
{  
  U16 ret;
 
  ret = cpu->Mem[cpu->PC >> 8] | cpu->Mem[cpu->PC];

  cpu->PC += 1;
 
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
	case 0x1: LD_reg_x16(COMB_REGS(cpu->b, cpu->c), cpu->SP); cpu->PC++; break;
	case 0x2: break;
	  
	//default: printf("Opcode 0x%X not found!", current_op); exit(0);
	}
    }
}

void print_regs(struct CPU *cpu)
{
  //print all the state of all the registers in the cpu
  printf("reg a : 0x%X\n", cpu->a);
  printf("reg f : 0x%X\n", cpu->f);
  printf("reg b : 0x%X\n", cpu->b);
  printf("reg c : 0x%X\n", cpu->c);
  printf("reg d : 0x%X\n", cpu->d);
  printf("reg e : 0x%X\n", cpu->e);
  printf("reg h : 0x%X\n", cpu->h);
  printf("reg l : 0x%X\n", cpu->l);
  
  //values of combined registers
  printf("reg af : 0x%X\n", COMB_REGS(cpu->a, cpu->f));
  printf("reg bc : 0x%X\n", COMB_REGS(cpu->b, cpu->c));
  printf("reg de : 0x%X\n", COMB_REGS(cpu->d, cpu->e));
  printf("reg hl : 0x%X\n", COMB_REGS(cpu->h, cpu->l));
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


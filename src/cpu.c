#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "opcodes.h"


void init_gb(struct CPU *cpu)
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


u16 fetch_opcode(struct CPU *cpu)
{  
  u16 ret;

  ret = cpu->Mem[cpu->PC >> 8] | cpu->Mem[cpu->PC];
  
  cpu->PC++;
  
  return ret;
}


void execute_opcodes(struct CPU *cpu)
{   
  struct Flags *f;
  u8 upper, lower;
  
  u16 current_op = fetch_opcode(cpu);
  
  upper = current_op & 0x00FF;
  lower = current_op >> 8;

  u8 op_queue[2] = {upper , lower};
  
  for(int i=0; i < 2; i++)
    {
      current_op = op_queue[i];
            
      switch(current_op)
	{  
	case 0x0:
	  NOP(cpu->PC);
	  cpu->PC++;
	  break;      
    
	case 0x1:
	  ld_r16_n16(combine_regs(cpu->b, cpu->c), cpu->PC + 2);
	  cpu->PC += 3;
	  break;
      
	case 0x2:
	  ld_r16_n8(combine_regs(cpu->Mem[cpu->b], cpu->Mem[cpu->c]), cpu->a); 
	  cpu->PC++;
	  break;
	  
	case 0x3:
	  inc_reg(combine_regs(cpu->b, cpu->c));
	  cpu->PC++; 
	  break;

	case 0x4:
	  inc_reg(cpu->b);
	  cpu->PC++;
	  break;

	case 0x5:
	  dec_reg(cpu->b);
	  cpu->PC++;
	  break;

	case 0x6:
	  ld_r8_n8(cpu->b, cpu->PC++);
	  cpu->PC += 2;
	  break;

	case 0x7:
	  rlca(cpu->a, f->c);
	  cpu->PC++;
	  break;

	case 0x8:
	  ld_r16_n16(cpu->Mem[cpu->PC + 2], cpu->SP);
	  cpu->PC += 3;
	  break;

	case 0x9:
	  add(combine_regs(cpu->h, cpu->l), combine_regs(cpu->b, cpu->c));
	  cpu->PC++;
	  break;

	case 0xA:
	  ld_r8_n16(cpu->a, cpu->Mem[combine_regs(cpu->b, cpu->c)]);
	  cpu->PC++;
	  break;
	  
	case 0xB:
	  dec_reg(combine_regs(cpu->b, cpu->c));
	  cpu->PC++;
	  break;

	case 0xC:
	  inc_reg(cpu->c);
	  cpu->PC++;
	  break;

	case 0xD:
	  dec_reg(cpu->c);
	  cpu->PC++;
	  break;

	case 0xE:
	  ld_r8_n8(cpu->c, cpu->PC++);
	  cpu->PC += 2;
	  break;

	case 0xF:
	  rrca(cpu->a, f->c);
	  cpu->PC++;
	  break;

	  switch(current_op & 0xFF)
	    {
	    case 0x00:
	      STOP(cpu->PC);
	      cpu->PC += 2;
	      break;

	    case 0x01:
	      ld_r16_n16(combine_regs(cpu->d, cpu->e), cpu->PC + 2);  
	      cpu->PC += 3;
	      break;

	    case 0x02:
	      ld_r16_n8(cpu->Mem[combine_regs(cpu->d, cpu->e)], cpu->a);
	      cpu->PC++;
	      break;

	    case 0x03:
	      inc_regs(combine_regs(cpu->d, cpu->e));
	      cpu->PC++;
	      break;

	    case 0x04:
	      inc_reg(cpu->d);
	      cpu->PC++;
	      break;

	      
	    }
	  
	  default: printf("Unsupported Opcode 0x%X\n", current_op); NOP(cpu->PC);
	}
    }
}

int main(void)
{
  struct CPU cpu;
  
  init_gb(&cpu);
  load_rom(&cpu);

  for(int i=0; i < 10; i++)
    {
      execute_opcodes(&cpu);
    }

  return 0;
}

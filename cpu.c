#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"


void init_gb(struct GB *gb)
{
  gb->op = 0;

  gb->SP = 0;
  gb->PC = 0x0100;

  for(int i=0; i < 0xFFFF; i++)
    {
      gb->Mem[i] = 1;
    }  
}

void load_rom(struct GB *gb)
{
  FILE *rom;

  rom = fopen("../roms/Dr. Mario (JU) (V1.1).gb", "rb");

  if(rom == NULL)
    {
      printf("File was not found");
    }

  fread(&gb->Mem[gb->PC], 1, 0xFFFF, rom);   
  fclose(rom);
}

 
U16 fetch_opcode(struct GB *gb)
{    
  U16 ret;

  U16 msb = gb->Mem[gb->PC];
  U16 lsb = gb->Mem[gb->PC + 1];

  ret = lsb << 16 | msb; 
      
  return ret;
}


U16 execute_opcode(struct GB *gb)
{
  gb->op = fetch_opcode(gb);

  printf("opcode: 0x%X\n", gb->op); 
}


int main()
{
  struct GB gameboy;
  
  init_gb(&gameboy);

  load_rom(&gameboy);

  fetch_opcode(&gameboy);  

  execute_opcode(&gameboy);
}

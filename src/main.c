#include <stdio.h>
#include "cpu.h"
#include "opcodes.h"


int main()
{
  struct GB gameboy;

  init_gb(&gameboy);
  load_rom(&gameboy); //load the rom into gameboy memory

  //only prints first instruction followed by 0s 
  for(int i=0; i < 20; i++)
    {
      execute_opcode(&gameboy);
    }
}

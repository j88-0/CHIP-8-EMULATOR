#include "systemVars.h"
#include <iostream>

class Chip8 {

  public:
// General purpose 8 bit registers below...
    int8_t v[0xF] = {0}; // All the registers from v0 to vF.

    int8_t DT; // Stands for the delay timer register.
    int8_t ST; // Stands for the sound timer register.

    int16_t I; // For storing memory addresses...

    int16_t pc; // Stands for program counter...

    int8_t sp; // Stands for stack pointer...
    int16_t stack[0xF] = {0}; // Stack which stores addresses that interpretter should return when finished with subroutines.

};

int main(int argc, char **argv) {

  Chip8 chip;


  

  /* For testing ...
  std::cout << "cpuV0:" << +chip.v[0] << std::endl;
  chip.v[0] = 3;
  std::cout << "cpuV0:" << +chip.v[0] << std::endl;
  */

  return 0;
}

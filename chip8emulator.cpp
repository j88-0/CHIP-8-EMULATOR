#include "system_vars.h"
#include "opcode_exec.h" 
#include <iostream>
#include <SDL2/SDL.h>

class Chip8 {

  public:
// General purpose 8 bit registers below...
    uint8_t v[0xF] = {0}; // All the registers from v0 to vF.

    uint8_t memory[ADDRESS_SPACE] = {0};

    uint8_t DT = 0; // Stands for the delay timer register.
    uint8_t ST = 0; // Stands for the sound timer register.

    uint16_t I = 0; // For storing memory addresses...

    uint16_t pc = 0; // Stands for program counter...

    uint8_t sp = 0; // Stands for stack pointer...
    uint16_t stack[0xF] = {0}; // Stack which stores addresses that interpretter should return when finished with subroutines.

    uint8_t drawFlag:1;
    uint8_t enabled:1;

    Chip8() {
      drawFlag = 0;
      enabled = 0;
      return;
    }

};

int main(int argc, char **argv) {

  if (argc != 2) {
    std::cerr << "Arguments required: [TARGET FILE]" << std::endl;
    return 1; // return 1 since their isn't the required amount of arguments.
  }
  // Testing SDL window creation ...
  int initErr = SDL_Init(SDL_INIT_EVERYTHING);
  if (initErr) {
    std::cerr << "Couldn't initialize SDL library: " << initErr << std::endl;
    return 1;
  }

  Chip8 chip;

  std::cout << sizeof chip << std::endl;

  SDL_Window *window;
  window = SDL_CreateWindow("chip8display",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,0);

  // Delay is just for testing...
  while (chip.enabled) {

  }

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}

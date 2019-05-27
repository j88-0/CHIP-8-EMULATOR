#include "systemVars.h"
#include <iostream>
#include <SDL2/SDL.h>

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

  // Testing SDL window creation ...
  int initErr = SDL_Init(SDL_INIT_EVERYTHING);
  if (!initErr) {
    std::cout << "Couldn't initialize SDL library: " << initErr << std::endl;
  }

  SDL_Surface *screen = SDL_SetVideoMode(600,500,16,SDL_SWSURFACE);

  //SDL_WM_SetCaption("~~chip8~~", "Chip8Display")

  SDL_Quit();

  /* For testing ...
  std::cout << "cpuV0:" << +chip.v[0] << std::endl;
  chip.v[0] = 3;
  std::cout << "cpuV0:" << +chip.v[0] << std::endl;
  */

  return 0;
}

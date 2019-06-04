#include "system_vars.h"
#include "opcode_exec.h"
#include <iostream>
#include <mingw.thread.h>
#include <chrono>

int loadProgram(); // Function decleratin for loading program into address space...
int updateGraphics();
int updateTimers();
int disassemble(uint16_t instruction);

Chip8 chip;
char *targetFile;

int main(int argc, char **argv) {

  if (argc != 2) {
    std::cerr << "Arguments required: [TARGET FILE]" << std::endl;
    return 1; // return 1 since their isn't the required amount of arguments.
  }

  int initErr = SDL_Init(SDL_INIT_EVERYTHING);
  if (initErr) {
    std::cerr << "Couldn't initialize SDL library: " << SDL_GetError() << std::endl;
    return 1;
  }

  targetFile = argv[1]; // Retrieves the target path/filename.

  SDL_Window *window = SDL_CreateWindow("chip8display",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);
  int RenderLogicErr = SDL_RenderSetLogicalSize(renderer,WINDOW_WIDTH,WINDOW_HEIGHT);
  if (RenderLogicErr) {
    std::cerr << "Couldn't set up renderer: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Texture *texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB888,SDL_TEXTUREACCESS_STREAMING,WINDOW_WIDTH,WINDOW_HEIGHT);

  SDL_SetRenderDrawColor(renderer,50,171,108,0);

  chip.enabled = 1;
  while (chip.enabled) {
    uint16_t instruction = (chip.memory[chip.pc] << 8) | chip.memory[chip.pc+1];
    disassemble(instruction); // Fetch, Decode, Execute
    updateTimers(); // Update the timer registers ST and DT... 
    if (chip.drawFlag) {
      updateGraphics();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 60 Hertz equates to 1000 milleseconds... // Time to wait for when emulating cycles.
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

int updateGraphics() {

  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  return 0;
}

int loadProgram() {

  return 0;
}

int updateTimers() {
  if (chip.DT > 0) {
    chip.DT--;
  }
  if (chip.ST > 0) {
    chip.ST--;
    std::cout << '\a' << std::endl; // sounds off the administration beep.
  }
  return 0;
}

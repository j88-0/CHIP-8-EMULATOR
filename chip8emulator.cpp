#include "system_vars.h"
#include "opcode_exec.h"
#include <iostream>
#include <new>
#include <istream>
#include <fstream>
#include <mingw.thread.h>
#include <chrono>

int loadProgram(); // Function decleratin for loading program into address space...
int updateGraphics();
int updateTimers();
int disassemble(uint16_t instruction);
int detectKeys();
int setUpSDL();
void safeExit();

Chip8 chip;
char *filePath;
SDL_Window *window; // Main components of SDL
SDL_Renderer *renderer; // Main components of SDL
SDL_Texture *texture;  // Main components of SDL

uint32_t pixels[ACTUAL_WIDTH*ACTUAL_HEIGHT];

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Arguments required: [TARGET FILE]" << std::endl;
    return 1; // return 1 since their isn't the required amount of arguments.
  }
  filePath = argv[1]; // Retrieves the target path/filename.

  if (setUpSDL()) {
    std::cerr << "SDL could not be setup" << std::endl;
    return 1;
  }

  if (loadProgram()) {
    std::cerr << "SDL could not be setup" << std::endl;
    return 1;
  }

  chip.enabled = 1;

  while (chip.enabled) {

    uint16_t instruction = (chip.memory[chip.pc] << 8) | chip.memory[chip.pc+1];
    // For testing purposes... std::cout << std::hex << +instruction << std::endl;
    disassemble(instruction); // Fetch, Decode, Execute

    if (chip.drawFlag) {
      updateGraphics();
    }

    updateTimers(); // Update the timer registers ST and DT...
    detectKeys();
    std::this_thread::sleep_for(std::chrono::milliseconds(6)); //roughly 60 Hertz refresh rate...  equates to 16666 microseconds... // Time to wait for when emulating cycles.

  }

  safeExit();

  return 0;
}

int updateGraphics() {

  chip.drawFlag = 0; // Deactivates drawing flag to not draw pointless if DRW opcode hasn't occured.

  for (int i = 0; i < ACTUAL_WIDTH*ACTUAL_HEIGHT; i++) {
    uint8_t pixel = chip.graphics[i];
    pixels[i] = (0x00FFFFFF * pixel) | 0xFF000000;
  }
  // Update SDL texture

  SDL_UpdateTexture(texture, NULL, pixels, ACTUAL_WIDTH*sizeof(uint32_t));
  // Clear screen and render
  SDL_RenderClear(renderer); // Clears the pixels buffer pixels with drawing color, making all bytes equal to 0.
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer); // Displays current renderer pixels.
  return 0;
}

int setUpSDL() {

  int initErr = SDL_Init(SDL_INIT_EVERYTHING);
  if (initErr) {
    std::cerr << "Couldn't initialize SDL library: " << SDL_GetError() << std::endl;
    return 1;
  }

  window = SDL_CreateWindow("chip8display",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "SDL Window could not be created: " << SDL_GetError() << std::endl;
    return 1;
  }

  renderer = SDL_CreateRenderer(window,-1,0);
  if (!renderer) {
    std::cerr << "SDL renderer could not be created: " << SDL_GetError() << std::endl;
    return 1;
  }


  int renderLogicErr = SDL_RenderSetLogicalSize(renderer,WINDOW_WIDTH,WINDOW_HEIGHT);
  if (renderLogicErr) {
    std::cerr << "Couldn't set up renderer's logical size: " << SDL_GetError() << std::endl;
    return 1;
  }

  texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,ACTUAL_WIDTH,ACTUAL_HEIGHT);
  if (!texture) {
    std::cerr << "Couldn't set up sdl texture: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_SetRenderDrawColor(renderer,255,255,255,0);
  return 0;
}

int loadProgram() {

  std::fstream fileStream;

  fileStream.open(filePath,std::fstream::in | std::fstream::binary);

  fileStream.seekg(0,std::ios_base::end);
  int fileSize = fileStream.tellg();
  fileStream.seekg(0,std::ios_base::beg);

  if (fileSize > (PROGRAM_END - PROGRAM_START)) {
    std::cerr << "The size of the program is to big. File size must be at most " << PROGRAM_END-PROGRAM_START << " bytes" << std::endl;
    return 1;
  }

  char* tempBuffer = new (std::nothrow) char[fileSize]; // Will need to edit this eventually...
  if (!tempBuffer) {
    std::cerr << "Temporary buffer failed to be allocated." << std::endl;
    return 1;
  }

  fileStream.read(tempBuffer,fileSize);

  for (int i = 0; i <= fileSize; i++) {
    chip.memory[i+PROGRAM_START] = (uint8_t)tempBuffer[i];
  }

  delete[] tempBuffer;

  fileStream.close(); // closes the file...

  return 0;
}

int updateTimers() {
  if (chip.DT > 0) {
    chip.DT--;
  }
  if (chip.ST > 0) {
    chip.ST--;
    std::cout << '\a' << std::endl; // sounds off the system beep.
  }
  return 0;
}

void safeExit() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
  if (window) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
  return;
}

int detectKeys()  {
   SDL_Event event;
   while (SDL_PollEvent(&event)) {
     switch (event.type) {
        case SDL_KEYDOWN:
            for (int i = 0; i <= 0xF; i++) {
              if (event.key.keysym.sym == chip.keySDLMap[i]) { // Line below is just for testing purposes.
                  chip.keyState[i] = 1;
              }
            }
        break;
        case SDL_KEYUP:
          for (int i = 0; i <= 0xF; i++) {
            if (event.key.keysym.sym == chip.keySDLMap[i]) { // Line below is just for testing purposes.
                chip.keyState[i] = 0;
            }
          }
        break;
        default:
          return 1;
      }
   }

   return 0;
}

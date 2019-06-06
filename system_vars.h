#ifndef SYSTEM_VARS_H
#define SYSTEM_VARS_H

#define SDL_MAIN_HANDLED

#include <cstdint>
#include <SDL2/SDL.h>

#define ADDRESS_SPACE 0x1000 // 1000 memory locations or 0x4096 locations.

#define PROGRAM_START 0x200 // Program starts at address 0x200/512.
#define PROGRAM_END 0xFFF // Program ends at address 0xFFF or 4096.

#define SPRITE_SIZE 0xF // Sprite size can be 15 bytes or 0xF bytes with size of 8x15.

#define WINDOW_WIDTH 640 // Windows width.
#define WINDOW_HEIGHT 320 // Windows height.

#define ACTUAL_WIDTH 64 // Actual width.
#define ACTUAL_HEIGHT 32 // Actual height.

class Chip8 {

  public:
// General purpose 8 bit registers below...
    uint8_t V[0x10] = {0}; // All the registers from v0 to vF.

    uint8_t memory[ADDRESS_SPACE] = {0};

    uint8_t keyState[0x10] = {0};
    uint8_t keySDLMap[0x10] = {
      SDLK_x, SDLK_1, SDLK_2, SDLK_3,
      SDLK_q, SDLK_w, SDLK_e, SDLK_a,
      SDLK_s, SDLK_d, SDLK_z, SDLK_c,
      SDLK_4, SDLK_r, SDLK_f, SDLK_v
    };
    uint8_t fontSet[80] = {
      0xF0, 0x90, 0x90, 0x90, 0xF0, //0
      0x20, 0x60, 0x20, 0x20, 0x70, //1
      0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
      0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
      0x90, 0x90, 0xF0, 0x10, 0x10, //4
      0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
      0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
      0xF0, 0x10, 0x20, 0x40, 0x40, //7
      0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
      0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
      0xF0, 0x90, 0xF0, 0x90, 0x90, //A
      0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
      0xF0, 0x80, 0x80, 0x80, 0xF0, //C
      0xE0, 0x90, 0x90, 0x90, 0xE0, //D
      0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
      0xF0, 0x80, 0xF0, 0x80, 0x80  //F
    };

    uint8_t DT = 0; // Stands for the delay timer register.
    uint8_t ST = 0; // Stands for the sound timer register.

    uint16_t I = 0; // For storing memory addresses...

    uint16_t pc = 0; // Stands for program counter...

    uint8_t sp = 0; // Stands for stack pointer...
    uint16_t stack[0x10] = {0}; // Stack which stores addresses that interpretter should return when finished with subroutines.

    uint8_t drawFlag:1;
    uint8_t enabled:1;

    uint8_t graphics[ACTUAL_WIDTH*ACTUAL_HEIGHT] = {0};
    // 64*32 resolution

    Chip8() {
      drawFlag = 0;
      enabled = 0;
      pc = 0x200;
      loadFontSet();
      return;
    }

    int loadFontSet() { // Fills in first of interpreters location in memory with the font set.
      for (int i = 0; i <= 80; i++) {
        memory[i] = fontSet[i];
      }
      return 0;
    }

};

#endif

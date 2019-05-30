#ifndef SYSTEM_VARS_H
#define SYSTEM_VARS_H
#define SDL_MAIN_HANDLED

#include <cstdint>

#define ADDRESS_SPACE 0x1000 // 1000 memory locations or 0x4096 locations.
#define ADDRESSABILITY 0x1 // 1 byte for addressability or 0x1 bytes.
#define INTP_MAPPING 0x0 // First 512 bytes or 0x200.

#define PROGRAM_START 0x200 // Program starts at address 0x200/512.
#define PROGRAM_END 0xFFF

#define SPRITE_SIZE 0xE // Sprite size can be 15 bytes or 0xE bytes with size of 8x15.

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 500

//extern Chip8 chip;

#endif

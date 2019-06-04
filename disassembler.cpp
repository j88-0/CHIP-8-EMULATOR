#include "opcode_exec.h"
#include "system_vars.h"
#include <sys/types.h> // This header and one below are for the open system command.
#include <fcntl.h> //

// extern defines global linkage ...
extern Chip8 chip;

int disassemble(uint16_t instruction) { 

  // This listing retrieves the actual values ...
  uint8_t fN = (instruction & 0xF000)>>12; // First nibble.
  uint16_t nnn = instruction & 0x0FFF;
  uint8_t n = instruction & 0x000F;
  uint8_t x = (instruction & 0x0F00)>>8;
  uint8_t y = (instruction & 0x00F0)>>4;
  uint8_t kk = instruction & 0x00FF;

  if (instruction == 0x00E0) {
    execCLS();
  }
  else if (instruction == 0x00EE) {
    execRET();
  }
  else {
    switch (fN) {
      case 0x0: execSYS(nnn); break;
      case 0x1: execJP(nnn); break;
      case 0x2: execCALL(nnn); break;
      case 0x3: execSE(x,kk); break;
      case 0x4: execSNE(x,kk); break;
      case 0x5: execSE2(x,y);  break;
      case 0x6: execLD(x,kk); break;
      case 0x7: execADD(x,kk); break;
      case 0x8: // CONTAINS MULTIPLE INSTRUCTIONS...
        switch (n) {
          case 0x0: execLD2(x,y); break;
          case 0x1: execOR(x,y); break;
          case 0x2: execAND(x,y); break;
          case 0x3: execXOR(x,y); break;
          case 0x4: execADD2(x,y); break;
          case 0x5: execSUB(x,y); break;
          case 0x6: execSHR(x); break;
          case 0x7: execSUBN(x,y); break;
          case 0xE: execSHL(x); break;
          default: return 1;
        }
      break;
      case 0x9: execSNE2(x,y); break;
      case 0xA: execLD3(nnn); break;
      case 0xB: execJP2(nnn); break;
      case 0xC: execRND(x,kk); break;
      case 0xD: execDRW(x,y,n); break;
      case 0xE:
        switch (n) {
          case 0xE: execSKP(x); break;
          case 0x1: execSKNP(x); break;
          default: return 1;
        }
      break;
      case 0xF:
        switch (kk) {
          case 0x07: execLD4(x); break;
          case 0x0A: execLD5(x); break;
          case 0x15: execLD6(x); break;
          case 0x18: execLD7(x); break;
          case 0x1E: execADD3(x); break;
          case 0x29: execLD8(x); break;
          case 0x33: execLD9(x); break;
          case 0x55: execLD10(x); break;
          case 0x65: execLD11(x); break;
          default: return 1;
        }
      default: return 1;
    }
  }

  return 0;
}

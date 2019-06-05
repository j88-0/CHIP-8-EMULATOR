#include "system_vars.h"
#include <time.h> // For generating a seed value for random value generation...

extern Chip8 chip;

void incPC() {
  chip.pc+=2;
  return;
}
/// Above method is just to increment the pc, quickly...
int execCLS() { // WILL NEED TO USE SDL FOR THIS...
  for (int i = 0; i < ACTUAL_WIDTH*ACTUAL_HEIGHT; i++) {
      chip.graphics[i] = 0; // all pixels back to black.
  }
  incPC();
  return 0;
}

int execRET() {
  chip.sp--;
  chip.pc = chip.stack[chip.sp];
  incPC();
  return 0;
}

int execSYS(uint16_t nnn) {
  chip.pc = nnn;
  return 0;
}
///////////////////////////////
int execJP(uint16_t nnn) {
  chip.pc = nnn;
  return 0;
}

int execCALL(uint16_t nnn) { // Will need to fix this...
  chip.stack[chip.sp] = chip.pc;
  chip.sp++;
  chip.pc = nnn;
  return 0;
}

int execSE(uint8_t x,uint8_t kk) {
  if (chip.V[x] == kk) {
    chip.pc+=4;
  }
  else {
    incPC();
  }
  return 0;
}

int execSNE(uint8_t x,uint8_t kk) {
  if (chip.V[x] != kk) {
    chip.pc+=4;
  }
  else {
    incPC();
  }
  return 0;
}

int execSE2(uint8_t x,uint8_t y) {
  if (chip.V[x] == chip.V[y]) {
    chip.pc+=4;
  }
  else {
    incPC();
  }
  return 0;
}

int execLD(uint8_t x,uint8_t kk) {
  chip.V[x] = kk;
  incPC();
  return 0;
}

int execADD(uint8_t x,uint8_t kk) {
  chip.V[x]+=kk;
  incPC();
  return 0;
}

int execLD2(uint8_t x,uint8_t y) {
  chip.V[x] = chip.V[y];
  incPC();
  return 0;
}

int execOR(uint8_t x,uint8_t y) {
  chip.V[x] |= chip.V[y];
  incPC();
  return 0;
}

int execAND(uint8_t x,uint8_t y) {
  chip.V[x] &= chip.V[y];
  incPC();
  return 0;
}

int execXOR(uint8_t x,uint8_t y) {
  chip.V[x] ^= chip.V[y];
  incPC();
  return 0;
}

int execADD2(uint8_t x,uint8_t y) { // To finish working on...
    chip.V[x]+=chip.V[y];
    if (chip.V[x] + chip.V[y] > 0xFF) {
      chip.V[0xF] = 1;
    }
    else {
      chip.V[0xF] = 0;
    }
  incPC();
  return 0;
}

int execSUB(uint8_t x,uint8_t y) {
  if (chip.V[x] > chip.V[y]) {
    chip.V[0xF] = 1;
  }
  else {
    chip.V[0xF] = 0;
  }
  chip.V[x]-=chip.V[y];
  incPC();
  return 0;
}

int execSHR(uint8_t x) { // Stands for divide by 2.
  chip.V[0xF] = chip.V[x] & 0x1;
  chip.V[x]>>=1;
  incPC();
  return 0;
}

int execSUBN(uint8_t x,uint8_t y) {
  if (chip.V[y] > chip.V[x]) {
    chip.V[0xF] = 1;
  }
  else {
    chip.V[0xF] = 0;
  }
  chip.V[x] = chip.V[y] - chip.V[x];
  incPC();
  return 0;
}

int execSHL(uint8_t x) {
  chip.V[0xF] = chip.V[x] >> 7; // Shifts and gives us the right most bit.
  chip.V[x]<<=1;
  incPC();
  return 0;
}

int execSNE2(uint8_t x,uint8_t y) {
  if (chip.V[x] != chip.V[y]) {
    chip.pc+=4;
  }
  else {
    incPC();
  }
  return 0;
}

int execLD3(uint16_t nnn) {
  chip.I = nnn;
  incPC();
  return 0;
}

int execJP2(uint16_t nnn) {
  chip.pc=nnn+chip.V[0];
  return 0;
}

int execRND(uint8_t x,uint8_t kk) {
  srand(time(NULL));
  chip.V[x] = (rand()%256) & kk;
  incPC();
  return 0;
}

int execDRW(uint8_t x,uint8_t y,uint8_t n) { // NEED SDL FOR USAGE...
  uint16_t pixel;
  chip.V[0xF] = 0;
  for (int yline = 0; yline < n; yline++) {
    pixel = chip.memory[chip.I + yline];
        for(int xline = 0; xline < 8; xline++) {
            if((pixel & (0x80 >> xline)) != 0) {
                if(chip.graphics[(x + xline + ((y + yline) * 64))] == 1) {
                    chip.V[0xF] = 1;
                }
                chip.graphics[x + xline + ((y + yline) * 64)] ^= 1;
            }
         }
  }

  chip.drawFlag = 1;
  incPC();
  return 0;
}

int execSKP(uint8_t x) {
  if (chip.keyState[chip.V[x]] != 0) {
    chip.pc+=4;
  }
  else {
    incPC();
  }
  return 0;
}

int execSKNP(uint8_t x) {
  if (chip.keyState[chip.V[x]] == 0) {
    chip.pc+=4;
  }
  else {
    incPC();
  }
  return 0;
}

int execLD4(uint8_t x) {
  chip.V[x] = chip.DT;
  incPC();
  return 0;
}

int execLD5(uint8_t x) {
  for (int i = 0; i <= 0xF; i++) {
    if (chip.keyState[i]) {
      chip.V[x] = i;
      incPC();
      break;
    }
  }
  return 0;
}

int execLD6(uint8_t x) {
  chip.DT = chip.V[x];
  incPC();
  return 0;
}

int execLD7(uint8_t x) {
  chip.ST = chip.V[x];
  incPC();
  return 0;
}

int execADD3(uint8_t x) {
  chip.I+=chip.V[x];
  incPC();
  return 0;
}

int execLD8(uint8_t x) {
  chip.I = chip.V[x]*0x5;
  incPC();
  return 0;
}

int execLD9(uint8_t x) {
  chip.memory[chip.I] = chip.V[x]/100;
  chip.memory[chip.I+1] = (chip.V[x]/10)%10;
  chip.memory[chip.I+2] = chip.V[x]%10;
  incPC();
  return 0;
}

int execLD10(uint8_t x) {
  uint16_t offset = 0;
  for (int reg = 0; reg <= x; reg++) {
      chip.memory[chip.I+offset] = chip.V[reg];
      offset++;
    }
  incPC();
  return 0;
}

int execLD11(uint8_t x) {
  uint16_t offset = 0;
  for (int reg = 0; reg <= x; reg++) {
    chip.V[reg] = chip.memory[chip.I+offset];
    offset++;
  }
  incPC();
  return 0;
}

#ifndef OPCODE_EXEC_H
#define OPCODE_EXEC_H

int execCLS();
int execRET();
int execSYS(uint16_t nnn);
int execJP(uint16_t nnn);
int execCALL(uint16_t nnn);
int execSE(uint8_t x,uint8_t kk);
int execSNE(uint8_t x,uint8_t kk);
int execSE2(uint8_t x,uint8_t y);
int execLD(uint8_t x,uint8_t kk);
int execADD(uint8_t x,uint8_t kk);
int execLD2(uint8_t x,uint8_t y);
int execOR(uint8_t x,uint8_t y);
int execAND(uint8_t x,uint8_t y);
int execXOR(uint8_t x,uint8_t y);
int execADD2(uint8_t x,uint8_t y);
int execSUB(uint8_t x,uint8_t y);
int execSHR(uint8_t x);
int execSUBN(uint8_t x,uint8_t y);
int execSHL(uint8_t x);
int execSNE2(uint8_t x,uint8_t y);
int execLD3(uint16_t nnn);
int execJP2(uint16_t nnn);
int execRND(uint8_t x,uint8_t kk);
int execDRW(uint8_t x,uint8_t y,uint8_t n);
int execSKP(uint8_t x);
int execSKNP(uint8_t x);
int execLD4(uint8_t x);
int execLD5(uint8_t x);
int execLD6(uint8_t x);
int execLD7(uint8_t x);
int execADD3(uint8_t x);
int execLD8(uint8_t x);
int execLD9(uint8_t x);
int execLD10(uint8_t x);
int execLD11(uint8_t x);

#endif

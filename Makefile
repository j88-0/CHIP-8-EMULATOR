CC=g++
CPPFLAGS=-D_WIN32_WINNT=0x0501

OBJECT_FILES= chip8emulator.o disassembler.o opcode_exec.o
EXEC_NAME=chip8emulator
EXEC=chip8emulator.exe
LIBS=SDL2

#-L./ Searches the current directory for the linker files.

chip8emulator: $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) -L. -l$(LIBS) $(CPPFLAGS) -o $(EXEC_NAME)
clean:
	rm -f $(OBJECT_FILES) $(EXEC)


name = test3

source = ./$(name).c
listing = ./test.c.asm
obj = ./test.c.asm.o
executable = ./test.c.executable

AS = as
GCC = gcc

# AS = riscv64-linux-gnu-as 
# GCC = riscv64-linux-gnu-gcc-10 -fPIC

.PHONY: all clean

all:
	../toy -o $(listing) $(source)
	$(AS) --gen-debug -o $(obj) $(listing)
	$(GCC) -g3 -o $(executable) $(obj)

clean:
	rm -f $(listing)
	rm -f $(obj)
	rm -f $(executable)

rebuild: clean all

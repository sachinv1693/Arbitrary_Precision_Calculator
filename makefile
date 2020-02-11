OBJ := $(patsubst %.c, %.o, $(wildcard *.c))
apc.exe : $(OBJ)
	gcc -o $@ $^
clean:
	rm *.o *.exe

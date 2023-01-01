all: ipiie.bin
clean:
	rm -f *.o ipiie.bin

ipiie.bin: main.c
	gcc -Wall -Wextra main.c -o ipiie.bin

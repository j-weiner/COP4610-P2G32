all: main

run:
	./main

main: main.c syscalls_wrap.h
	gcc -O0 -g -o $@ $<

.PHONY: all clean run

clean:
	$(RM) main *.o
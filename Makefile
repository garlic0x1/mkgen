CC=clang
CFLAGS=-I.
DEPS=./project.h ./file.h 
SOURCES=./file.c ./main.c ./project.c 

%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)



source: $(SOURCES)
	$(CC) -g -o a.out $(SOURCES)
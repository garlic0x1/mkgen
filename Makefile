CC=clang
CFLAGS=-I.
DEPS=./project.h ./file.h 
SOURCES=./fs/dir.c ./file.c ./main.c ./project.c 

%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)



mkgen: $(SOURCES)
	$(CC) -g -o a.out $(SOURCES)
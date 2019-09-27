CC=gcc
CFLAGS= -g -Wall -lGL -lGLU -lglut -lm
DEPS = # headers
OBJ = main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	-rm -f *.o main
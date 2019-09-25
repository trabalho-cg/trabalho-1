CC=gcc
CFLAGS= -g -Wall -Werror -lGL -lGLU -lglut
DEPS = # headers
OBJ = main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	-rm -f *.o main
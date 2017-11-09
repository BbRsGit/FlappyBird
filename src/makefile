CC=gcc
CFLAGS=-I -m32 -O2 -lSDL2 -lSDL2_ttf -lSDL2_image
DEPS = draw.h flappy.h input.h res_manager.h score.h setup.h state_manager.h towers.h
OBJ = draw.o flappy.o input.o main.o res_manager.o score.o setup.o state_manager.o towers.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ)
	gcc -o $@ $^ -lm $(CFLAGS) 


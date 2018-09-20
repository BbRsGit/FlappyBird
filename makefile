CC=gcc
CFLAGS=-I -O2 -lSDL2 -lSDL2_ttf -lSDL2_image -Wall -Werror
DEPS = src/draw.h src/flappy.h src/input.h src/res_manager.h src/score.h src/setup.h src/state_manager.h src/towers.h
OBJ = src/draw.o src/flappy.o src/input.o src/main.o src/res_manager.o src/score.o src/setup.o src/state_manager.o src/towers.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Flappy: $(OBJ)
	gcc -o $@ $^ -lm $(CFLAGS) 


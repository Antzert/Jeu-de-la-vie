EXEC=JeuDeLaVie
CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic-errors -O3 -std=c17
LDFLAGS=-lSDL2 -lSDL2_ttf

build: all clean

clean :
	rm -f bin/*.o

all : bin bin/$(EXEC) bin/assets

bin/$(EXEC) : bin/main.o bin/game.o bin/GameWindow.o
	gcc $(CFLAGS) bin/*.o -o bin/$(EXEC) $(LDFLAGS)

bin/assets:
	cp -r assets bin
	
bin:
	mkdir bin

bin/main.o : src/main.c
	gcc -c $(CFLAGS) src/main.c -o bin/main.o $(LDFLAGS)
		
bin/game.o : src/game.c
	gcc -c $(CFLAGS) src/game.c -o bin/game.o $(LDFLAGS)	

bin/GameWindow.o : src/GameWindow.c
	gcc -c $(CFLAGS) src/GameWindow.c -o bin/GameWindow.o $(LDFLAGS)
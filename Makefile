CC=gcc
CFLAGS=-ggdb -Wall -Wextra --std=c99 --pedantic `pkg-config --cflags ncurses`
LIBS=`pkg-config --libs ncurses`

run: digiapp
	@./digiapp

digiapp: main.c
	@$(CC) $(CFLAGS) -o digiapp main.c $(LIBS)
debug: digiapp
	@gdb digiapp

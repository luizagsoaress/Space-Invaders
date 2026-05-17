CC = gcc
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	
install:
	$(CC) interface/inicio.c -o interface/inicio $(LIBS)
	mkdir -p ~/.local/bin
	mkdir -p ~/.local/share/spaceInvaders
	cp interface/inicio ~/.local/bin/inicio
	cp -r assets interface ~/.local/share/spaceInvaders
	chmod +x ~/.local/bin/inicio

run: 
	~/.local/bin/inicio
CC=g++
UNAME=$(shell uname -s)
CFLAGS=-c -g -Wall -Dmain=SDL_main
# Mac OS X Users: Remove -lmingw32 and remove  -w -Wl,-subsystem,windows
ifeq ($(UNAME),Darwin)
	LDFLAGS=-I/usr/local/include/SDL2 -I/usr/local/opt/sqlite/include -L/usr/local/lib -L/usr/local/opt/sqlite/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lsqlite3
else
	LDFLAGS=-I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf  —lsqlite -w -Wl,-subsystem,windows
endif
SOURCES=model.cpp view.cpp controller.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=final.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE):
	gcc -shared sqlite3.c -o sqlite3.dll
	$(CC) -g $(SOURCES) $(LDFLAGS) -o $@

clean:
	rm $(EXECUTABLE)

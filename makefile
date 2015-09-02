
CC        =  gcc

ifdef GCOV
CFLAGS   +=  -fprofile-arcs -ftest-coverage
LDFLAGS  +=  -fprofile-arcs -ftest-coverage
endif

ifdef STATIC
LDFLAGS  +=  $(shell sdl-config --static-libs)
else
LDFLAGS  +=  $(shell sdl-config --libs)
LDFLAGS  +=  -lGL -lm #-framework OpenGL
endif

CFLAGS   +=  $(shell sdl-config --cflags)
CFLAGS   +=  -ansi -Wall
CFLAGS   +=  -g
CFLAGS   +=  -ggdb
CFLAGS   +=  -pedantic

SRC       =  main.c audio.c video.c bitfont.c
OBJ       =  $(SRC:.c=.o)
BIN       =  demo

%.o: %.c
	$(CC) -c $(CFLAGS) $<

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@

bitfont-tool: bitfont.o bitfont-tool.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(BIN) *.o

.PHONY: clean


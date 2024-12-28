CC = gcc

CFLAGS = -lglut -lGL -lGLU -lm

SRCS = renderer.c

all: $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -o renderer

clean:
	rm -f renderer

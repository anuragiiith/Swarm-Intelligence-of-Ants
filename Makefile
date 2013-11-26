CC = g++
CFLAGS = -Wall
PROG = qwerty

SRCS = main.cpp
LIBS = -w -lglut -lGL -lGLU -lm

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)

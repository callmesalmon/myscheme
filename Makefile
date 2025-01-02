.DEFAULT_GOAL=/usr/local/bin/myscm
.PHONY: all

CC          = g++
CFLAGS      = -I./include
CPP_OBJS    = $(wildcard src/*.cpp)
CPP_HEADERS = $(wildcard include/*.hpp)

all: $(.DEFAULT_GOAL)

$(.DEFAULT_GOAL): $(CPP_OBJS) $(CPP_HEADERS)
	$(CC) $(CFLAGS) $(CPP_OBJS) -o $(.DEFAULT_GOAL)

clean:
	rm $(.DEFAULT_GOAL)

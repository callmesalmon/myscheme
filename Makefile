.DEFAULT_GOAL=/usr/local/bin/myscm

CC       = gcc
CFLAGS   = -I./include
CPP_OBJS = $(wildcard src/*.cpp)

all: $(.DEFAULT_GOAL)

$(.DEFAULT_GOAL): $(CPP_OBJS)
	gcc $(CFLAGS) $(CPP_OBJS) -o $(.DEFAULT_GOAL)

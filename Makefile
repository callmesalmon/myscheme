.DEFAULT_GOAL=/usr/local/bin/myscm
.PHONY: all

include config.mk

CPP_OBJS    = $(wildcard src/*.cpp)
CPP_HEADERS = $(wildcard include/*.hpp)
C_HEADERS   = $(wildcard include/*.h)

all: $(.DEFAULT_GOAL)

$(.DEFAULT_GOAL): $(CPP_OBJS) $(CPP_HEADERS) $(C_HEADERS)
	$(CC) $(CFLAGS) $(CPP_OBJS) -o $(.DEFAULT_GOAL)

clean:
	rm $(.DEFAULT_GOAL)
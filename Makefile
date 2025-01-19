.DEFAULT_GOAL=/usr/local/bin/myscm
.PHONY: all

include config.mk

CPP_OBJS      = $(wildcard src/*.cpp)
CPP_HEADERS   = $(wildcard include/*.h)

CONFIG_OUTPUT = $(wildcard config.*)
CONFIG_FILES  = $(CONFIG_OUTPUT) configure

all: $(.DEFAULT_GOAL)

$(.DEFAULT_GOAL): $(CPP_OBJS) $(CPP_HEADERS) $(CONFIG_FILES)
	$(CC) $(CFLAGS) $(CPP_OBJS) -o $(.DEFAULT_GOAL)

clean:
	rm $(.DEFAULT_GOAL)
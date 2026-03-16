.PHONY: all

include config.mk

CPP_OBJS      = $(wildcard src/*.cpp)
CPP_HEADERS   = $(wildcard include/*.h)

CONFIG_OUTPUT = $(wildcard config.*)
CONFIG_FILES  = $(CONFIG_OUTPUT) configure

TARGET        = myscm

all: build

build: $(CPP_OBJS) $(CPP_HEADERS) $(CONFIG_FILES)
	$(CC) $(CFLAGS) $(CPP_OBJS) -o $(TARGET)

install:  $(CPP_OBJS) $(CPP_HEADERS) $(CONFIG_FILES)
	$(CC) $(CFLAGS) $(CPP_ONJS) -o /usr/local/bin/$(TARGET)


clean:
	rm $(TARGET)
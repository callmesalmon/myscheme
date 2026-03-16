.PHONY: all

CPP_OBJS = $(shell find src/ -name '*.cpp')
CPP_HEADERS = $(shell find src/ -name '*.h')
TARGET = myscm

all: build

build: $(CPP_OBJS) $(CPP_HEADERS)
	$(CC) $(CFLAGS) $(CPP_OBJS) -o $(TARGET)

install:  $(CPP_OBJS) $(CPP_HEADERS)
	$(CC) $(CFLAGS) $(CPP_OBJS) -o /usr/local/bin/$(TARGET)


clean:
	rm $(TARGET)
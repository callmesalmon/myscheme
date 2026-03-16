.PHONY: all

CPP_OBJS      = $(wildcard src/*.cpp)
CPP_HEADERS   = $(wildcard include/*.h)

TARGET        = myscm

all: build

build: $(CPP_OBJS) $(CPP_HEADERS)
	$(CC) $(CFLAGS) $(CPP_OBJS) -o $(TARGET)

install:  $(CPP_OBJS) $(CPP_HEADERS)
	$(CC) $(CFLAGS) $(CPP_ONJS) -o /usr/local/bin/$(TARGET)


clean:
	rm $(TARGET)
CC = C:/msys64/ucrt64/bin/gcc.exe

CFLAGS = -IC:/msys64/ucrt64/include
LDFLAGS = -LC:/msys64/ucrt64/lib
LDLIBS = -lSDL3

TARGET = pixel.exe
SOURCE = pixel.c

.PHONY: all build run clean

all: build

build:
	$(CC) $(SOURCE) -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

run: build
	./$(TARGET)

clean:
	del $(TARGET)

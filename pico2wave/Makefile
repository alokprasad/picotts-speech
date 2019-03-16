CC = gcc -g -m32
TARGET = pico2wave
LIBS = -lexpat -lsvoxpico -lm -lpopt
LDFLAGS = -m32 -L/lib32 -L/usr/lib32
SOURCES  := $(wildcard src/pico2wave.c)

#for command line option demo uncomment below
#SOURCES  := $(wildcard src/pico2wave-org.c)

all:
	$(CC) $(SOURCES) -I../picotts-src/src -L../picotts-src $(LIBS) -I../compat/include/  -o $(TARGET)
	#$(CC) -I./. -L./. -I../picotts-src $(LIBS) -I../compat/include/  -o $(TARGET)

clean:
	rm -rf obj libs pico2wave


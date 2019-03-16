CC = g++ -g -m32 -Wall -g -O -fPIC -shared
TARGET = libspeech.so
LIBS = -lexpat -lsvoxpico -lm -lpopt
LDFLAGS = -shared -m32 -L/lib32 -L/usr/lib32
SOURCES  := $(wildcard src/speech.cpp)

#for command line option demo uncomment below
#SOURCES  := $(wildcard src/pico2wave-org.c)

all:	

	$(CC) $(SOURCES) -I./include -I./picotts-src/src -L./picotts-src $(LIBS) -o $(TARGET)
	#$(CC) -I./. -L./. -I../picotts-src $(LIBS) -I../compat/include/  -o $(TARGET)


clean:
	rm -rf libspeech.so


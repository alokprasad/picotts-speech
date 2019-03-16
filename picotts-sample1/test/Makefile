CC = g++ -g -m32 -Wall 
TARGET = testapp
LIBS =  -lsvoxpico -lspeech
LDFLAGS =  -m32 -L/lib32 -L/usr/lib32
SOURCES  := test.cpp

#for command line option demo uncomment below
#SOURCES  := $(wildcard src/pico2wave-org.c)

all:	

	#$(CC) $(SOURCES) -L./. -I./src -I../picotts-src/src -L../picotts-src $(LIBS) -I../compat/include/  -o $(TARGET)
	#$(CC) -I./. -L./. -I../picotts-src $(LIBS) -I../compat/include/  -o $(TARGET)
	$(CC) $(SOURCES) -L../. -I../include -I../picotts-src/src -L../picotts-src $(LIBS) -I../compat/include/  -o $(TARGET)

clean:
	rm -rf testapp 


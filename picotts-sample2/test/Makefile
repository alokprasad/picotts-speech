CC = g++ -g -m32 -Wall 
TARGET = testpico
LIBS =  -lsvoxpico -lttscompat
LDFLAGS :=  -m32 -L/lib32 -L/usr/lib32
SOURCES  := testpico.cpp
#for command line option demo uncomment below
#SOURCES  := $(wildcard src/pico2wave-org.c)

all:	

	#$(CC) $(SOURCES) -L./. -I./src -I../picotts-src/src -L../picotts-src $(LIBS) -I../compat/include/  -o $(TARGET)
	#$(CC) -I./. -L./. -I../picotts-src $(LIBS) -I../compat/include/  -o $(TARGET)
	$(CC) $(SOURCES) -L../lib -I../src -I../picotts-src/src -L../picotts-src $(LIBS) -I../compat/include/  -o $(TARGET) -Wl,-R,'$$ORIGIN/../lib'
clean:
	rm -rf testpico 


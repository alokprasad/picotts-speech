CC = g++ -g -m32 -Wall -g -O -fPIC -shared
TARGET = libttscompat.so
LIBS = -lexpat -lsvoxpico
LDFLAGS = -shared -m32 -L/lib32 -L/usr/lib32
SOURCES  := $(wildcard src/*.cpp )
OBJDIR   := obj
TARGETDIR := lib

all:
	@mkdir -p $(TARGETDIR)
	$(CC) $(SOURCES) -I./include -I./picotts-src/src -L./picotts-src $(LIBS) -o $(TARGETDIR)/$(TARGET)

clean:
	rm -rf $(TARGETDIR)/$(TARGET)

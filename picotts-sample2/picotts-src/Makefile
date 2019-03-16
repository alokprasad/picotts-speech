CC = gcc # C compiler
CFLAGS = -m32 -fPIC -Wall -Wextra -O2 -g # C flags
#CFLAGS += -D_WIN32
LDFLAGS = -m32 -shared  # linking flags
RM = rm -f  # rm command
TARGET_LIB = libsvoxpico.so # target lib
 
#SRCS = main.c src1.c src2.c # source files
SRCS=$(wildcard src/*.c)

OBJS = $(SRCS:.c=.o)
 
.PHONY: all
all:${TARGET_LIB}
	-${RM} ${OBJS} $(SRCS:.c=.d)	 
$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^


#$(SRCS:.c=.d):%.d:%.c
$(SRCS:.c):%.c
	$(CC) $(CFLAGS) -MM $< >$@
 
include $(SRCS:.c)
 
.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)

install:
	@echo "Copying the library to /usr/lib/"
	@cp libsvoxpico.so /usr/lib/

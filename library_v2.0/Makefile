.SUFFIXES : .c .o

CC = gcc

TARGET = emp

INC = -I.
LDFLAGS = -lpthread -lrt
#CFLAGS  = -O2
#CFLAGS += -Wall
#CFLAGS += -Wpedantic -std=c90

OBJS   = main.o BOOK.o MEM.o RENT.o STD.o

CFLAGS += $(INC) 
SRCS = $(OBJS:.o=.c) 

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -lm -o $@ $^ $(LDFLAGS) 

.c.o:
	$(CC) -c $(CFLAGS) $<

dep :
	$(CC) -M $(INC) $(SRCS) > .depend

clean :
	rm -rf $(OBJS) $(TARGET) core
	
distclean: clean
	rm -rf .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif 

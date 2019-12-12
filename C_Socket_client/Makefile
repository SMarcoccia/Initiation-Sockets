
CC = gcc
CFLAGS = -O3 -g -Wall -DEBUG
CCCOM = $(CC) $(CFLAGS) -std=c11
LDLIBS = \mingw\lib 
LDFLAGS = -L$(LDLIBS) -lws2_32
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
EXE = socket_client.exe

All: $(EXE)

$(EXE): $(OBJS)
	$(CCCOM) -o $@ $^ $(LDFLAGS)

.PHONY: clean mrproper

clean: 
	$(RM) *.o *~ *.stackdump *.bak *.makefile

mrproper: clean
	$(RM) $(EXE)
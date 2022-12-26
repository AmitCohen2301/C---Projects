CC = gcc
OBJS = loopcmp.o
EXEC = loopCmpProg
DEBUG = -g
COMP_FLAG = -std=c99 -Wall

$(EXEC) : $(OBJS)
	$(CC) $? -o $@

prog : loopcmp.c
	$(CC) $(DEBUG) $(COMP_FLAG) $?

clean :
	rm -f *.o $(EXEC)

CC = gcc
EXEC = primeCountProg
OBJS = primecount.o
OBJC = primecount.c
DEBUG = -g
COMP_FLAG = -c -std=gnu11 -Wall
SQRT_FLAG = -lm

$(EXEC) : $(OBJS)
	$(CC) $? -o $@ $(SQRT_FLAG)

$(OBJS) : $(OBJC)
	$(CC) $(DEBUG) $(COMP_FLAG) $?

clean :
	rm -f *.o $(EXEC)

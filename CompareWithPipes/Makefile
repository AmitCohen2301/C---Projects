OBJS = nicecmp.c
OBJS1 = loopcmp.c
CC = gcc
EXEC = nicecmp
EXEC1 = loopcmp
DEBUG_FLAG = -g
CFLAGS = -std=c99 -Wall -o


all: $(EXEC) $(EXEC1) 

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $@ $(OBJS)
	
$(EXEC1): $(OBJS1)
	$(CC) $(CFLAGS) $@ $(OBJS1)


clean :
	rm -f $(EXEC) $(EXEC1)


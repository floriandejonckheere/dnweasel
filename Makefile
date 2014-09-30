CFLAGS		= -W -Wall
LIBRARIES	= 
BINARY		= dnweasel

all: dnweasel

dnweasel: dnweasel.c
	$(CC) $(CFLAGS) $(LIBRARIES) -o $(BINARY) dnweasel.c

clean:
	rm -f $(BINARY) *.o

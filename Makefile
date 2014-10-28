CC	:= gcc
CFLAGS	:= -g -fPIC -g -O3 -Wall -Werror
LDFLAGS	:= -lm
LIB	:= weasel

BINNAME	:= dnweasel
TEST	:= weasel_test

all: $(BINNAME) $(TEST)

$(TEST):
	$(CC) $(CFLAGS) $(TEST).c $(LIB).c -o $(TEST) $(LDFLAGS)

$(BINNAME):
	$(CC) $(CFLAGS) $(BINNAME).c $(LIB).c -o $(BINNAME) $(LDFLAGS)

clean:
	$(RM) $(BINNAME) $(TEST)

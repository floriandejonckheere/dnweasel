CC	:= gcc
CFLAGS	:= -g -fPIC -g -O3 -Wall -Werror
LDFLAGS	:= -lm
MAJOR	:= 0
MINOR	:= 1
VERSION	:= $(MAJOR).$(MINOR)

LIBNAME	:= weasel
BINNAME	:= dnweasel

default: $(BINNAME)

all: default lib test

lib: lib$(LIBNAME).so.$(VERSION)

test: $(LIBNAME)_test
	LD_LIBRARY_PATH=. ./$(LIBNAME)_test

$(BINNAME): lib$(LIBNAME).so
	$(CC) $(BINNAME).c -o $@ -L. -l$(LIBNAME) $(LDFLAGS)

$(LIBNAME)_test: lib$(LIBNAME).so
	$(CC) $(LIBNAME)_test.c -o $@ -L. -l$(LIBNAME) $(LDFLAGS)

lib$(LIBNAME).so: lib$(LIBNAME).so.$(VERSION)
	ldconfig -v -n .
	ln -s lib$(LIBNAME).so.$(MAJOR) lib$(LIBNAME).so

lib$(LIBNAME).so.$(VERSION): $(LIBNAME).o
	$(CC) -shared -Wl,-soname,lib$(LIBNAME).so.$(MAJOR) $^ -o $@

clean:
	$(RM) $(BINNAME) $(LIBNAME)_test *.o *.so*

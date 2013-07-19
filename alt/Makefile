prefix = $(HOME)

CC = gcc
INSTALL = install
RM = rm -f

CFLAGS = -Wall -Werror -O2
LDFLAGS =

PROG = ps2logo
OBJS = ps2logo.o

all: $(PROG)

$(PROG): $(OBJS)

install: all
	$(INSTALL) -d -m 755 '$(prefix)/bin/'
	$(INSTALL) $(PROG) '$(prefix)/bin/'

clean:
	$(RM) $(PROG) $(OBJS)

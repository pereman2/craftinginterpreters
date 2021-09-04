IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -g
SAVETEMPS=-save-temps
SAVETEMPS=

ODIR=obj
LDIR =../lib

LIBS=-lm

_SOURCE = $(wildcard *.c)
OBJ = $(patsubst %.c, $(ODIR)/%.o, $(_SOURCE))
ASM = $(patsubst %.c, $(ODIR)/%.s, $(_SOURCE))
DEPS = $(patsubst %.h,$(IDIR)/%,$(_DEPS))


$(ODIR)/%.o: %.c
	$(CC) $(SAVETEMPS) -o $@ $< $(CFLAGS) -c

# $(ODIR)/%.o: $(ASM)
# 	$(CC) -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm -f *.s *~ core $(INCDIR)/*~
	rm -f *.bc *~ core $(INCDIR)/*~
	rm -f *.i *~ core $(INCDIR)/*~

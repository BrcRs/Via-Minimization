CC = gcc
COMPILE = $(CC) -fPIC -c
LINK = $(CC) -o $@
CFLAGS = -Wall

BINDIR := bin
SRCDIR := src

PROGRAMS = testbalayage testintersec testsegListUnion test_tools

SRCS := src/*.c

OBJS = $(SRCS:.c=.o)


all: check $(PROGRAMS)
	-mv *.o $(BINDIR)

check :
	-cd $(BINDIR) ; mv -t .. *.o
#Compilation

%.o : $(SRCDIR)/%.c
	$(CC) -c $< $(CFLAGS) -o $@

#Edition des liens


testbalayage: testbalayage.o intersec.o balayage.o Netlist.o hachage.o tools.o
	-$(LINK) testbalayage.o intersec.o balayage.o Netlist.o hachage.o tools.o

testintersec: testintersec.o Netlist.o intersec.o tools.o
	-$(LINK) testintersec.o Netlist.o intersec.o tools.o

testsegListUnion: testsegListUnion.o Netlist.o tools.o
	-$(LINK) testsegListUnion.o Netlist.o tools.o

test_tools: test_tools.o tools.o
	-$(LINK) test_tools.o tools.o

svgtest: svgtest.o svgNetlist.o
	-$(LINK) svgtest.o svgNetlist.o


clean:
	rm -f *.o $(PROGRAMS)
	cd $(BINDIR); 	rm -f *.o
	cd $(SRCDIR); rm -f *.o

.PHONY: clean all

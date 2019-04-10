CC = gcc
COMPILE = $(CC) -g3 -c
LINK = $(CC) -o $@
CFLAGS = -Wall

BINDIR := bin
SRCDIR := src

PROGRAMS = testGraph testMini7

SRCS := src/*.c

OBJS = $(SRCS:.c=.o)

OBJSA = PartieA/src/Netlist.o PartieA/src/tools.o PartieA/src/intersec.o

all: makeA check $(PROGRAMS)
	-mv *.o $(BINDIR)
	
	
makeA:
	cd PartieA ; make
	
check :
	-cd $(BINDIR) ; mv -t .. *.o
	
# Compilation

%.o : $(SRCDIR)/%.c
	$(CC) -c $< $(CFLAGS) -o $@
	

# Edition des liens
testGraph: testGraph.o generatePostScript.o graph.o $(OBJSA)
	$(LINK) testGraph.o generatePostScript.o graph.o $(OBJSA)

testMini7: testMini7.o graph.o viaMinimization.o $(OBJSA)
	$(LINK) testMini7.o viaMinimization.o graph.o $(OBJSA)
clean:
	cd PartieA ; make clean
	-rm -f *.o $(PROGRAMS)
	-cd $(BINDIR) ; rm -f *.o
	
.PHONY: clean all check makeA



CCOPTS=-Wall -std=c++11 -O3
OBJDIR=obj
BINDIR=bin

all: $(OBJDIR) $(BINDIR) bin/sw

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

bin/sw: obj/stopwatch.o src/main.cpp
	g++ $(CCOPTS) -o $@ $^

obj/stopwatch.o: src/stopwatch.cpp src/header/stopwatch.h
	g++ $(CCOPTS) -o $@ -c src/stopwatch.cpp

clear:
	rm obj/* bin/sw
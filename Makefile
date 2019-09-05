
CXXFLAGS=-g -O0 -std=c++11

OBJS = \
	linedriver.o \
	linedriverios.o \
	linedriverpre.o \
	getopt.o \
	typoerror.o \
	typograph.o \
	typographblock.o \
	typographblockattrs.o \
	typographblockbox.o \
	typographblockcols.o \
	typographblockholder.o \
	typographblockpar.o \
	typographblockseq.o \
	typographblocktext.o \
	typographstate.o \
	typotokenizer.o

TARGETS = ondrart.a main

all: $(TARGETS)

ondrart.a: $(OBJS)
	ar rcs $@ $^
	
main: main.o ondrart.a
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr $(TARGETS) $(OBJS) main.o

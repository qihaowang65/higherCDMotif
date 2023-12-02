INCLUDES= -I ./lib/
CC=g++
CFLAGS=-c -O3

SOURCES= lib/debugger.cpp lib/TwoTask.cpp lib/dfs.cpp lib/dfs2.cpp lib/counter.cpp lib/nestedmap.cpp lib/disjointset.cpp lib/util.cpp ccd.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=CCD


all:	$(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< $(INCLUDES) -o $@  



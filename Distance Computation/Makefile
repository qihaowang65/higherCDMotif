INCLUDES= -I ./lib/
CC=g++
CFLAGS=-c -O3

SOURCES= lib/debugger.cpp lib/counter.cpp lib/edgeadj.cpp lib/nestedmap.cpp lib/util.cpp distance.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=distance


all:	$(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< $(INCLUDES) -o $@  



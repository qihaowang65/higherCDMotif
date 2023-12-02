INCLUDES= -I ./lib/
CC=g++
CFLAGS=-c -O3

SOURCES= lib/debugger.cpp lib/counter.cpp lib/edgeadj.cpp lib/nestedmap.cpp lib/randomwalk.cpp lib/util.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main


all:	$(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< $(INCLUDES) -o $@  


clean:
	del main.o
	del main.exe

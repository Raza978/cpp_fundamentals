#make clean
#make all
#.\output.exe in windows
#./output in linux

CC = g++
CXXFLAGS = -std=c++11 -Wall -g -Wno-implicit-function-declaration
SOURCES := $(wildcard *.cpp) $(wildcard *.c)	#list all source files (.cpp, .c)
OBJS = $(SOURCES:.c=.o) #list all object files (.o)

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o output

clean:
	rm *.o *.exe

show:
	echo $(SOURCES)
CC = g++
CFLAGS = -O2 -Wall -g -std=c++11

install: genmk

genmk: genmk.o message.o MKTools.o 
	$(CC) $(CFLAGS) genmk.o message.o MKTools.o -o bin/genmk

genmk.o: genmk.cpp
	$(CC) $(CFLAGS) -c genmk.cpp
    
message.o: message.cpp message.h
	$(CC) $(CFLAGS) -c message.cpp
    
MKTools.o: MKTools.cpp MKTools.h
	$(CC) $(CFLAGS) -c MKTools.cpp
    
clean:
	rm -v *.o 

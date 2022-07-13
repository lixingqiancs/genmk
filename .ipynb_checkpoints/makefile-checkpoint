CC = g++
CFLAGS = -O2 -Wall -g

install: create_pipeline

create_pipeline: create_pipeline.o message.o MKTools.o 
	$(CC) $(CFLAGS) create_pipeline.o message.o MKTools.o -o bin/create_pipeline

create_pipeline.o: create_pipeline.cpp
	$(CC) $(CFLAGS) -c create_pipeline.cpp
    
message.o: message.cpp message.h
	$(CC) $(CFLAGS) -c message.cpp
    
MKTools.o: MKTools.cpp MKTools.h
	$(CC) $(CFLAGS) -c MKTools.cpp
    
clean:
	rm -v *.o 
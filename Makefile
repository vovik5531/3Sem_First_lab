CC=g++
CFLAGS=-c -Wall 
bin: main.o 
		$(CC) main.o -o bin
		rm *.o 
main.o: main.cpp
		$(CC) $(CFLAGS) main.cpp 
#test.o: test.cpp
#		$(CC) $(CFLAGS) test.cpp
# unique_ptr.o: Unique_ptr.cpp
# 		$(CC) $(CFLAGS) Unique_ptr.cpp
clean: 
		rm *.o

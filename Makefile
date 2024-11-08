CC=g++
CFLAGS=-c -Wall -Wextra

bin: main.o test.o timeTests.o
		$(CC)  test.o timeTests.o main.o -o bin -fsanitize=address -static-libasan
		rm *.o 
test.o: test.cpp
		$(CC) $(CFLAGS) test.cpp -fsanitize=address -g
timeTests.o: timeTests.cpp
		$(CC) $(CFLAGS) timeTests.cpp -fsanitize=address -g
main.o: main.cpp
		$(CC) $(CFLAGS) main.cpp -fsanitize=address -g
# unique_ptr.o: Unique_ptr.cpp
# 		$(CC) $(CFLAGS) Unique_ptr.cpp
clean: 
		rm *.o

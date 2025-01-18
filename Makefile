CC=g++
CFLAGS=-c -Wall -Wextra
# all: bin sfml-app
# sfml-app: plotting.o
# 		$(CC) plotting.o -o sfml-app -L/lib/SFML-2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

export LD_LIBRARY_PATH=/lib/SFML-2.6.1/lib
bin: main.o test.o timeTests.o UI.o plotting.o
		$(CC) test.o timeTests.o main.o plotting.o UI.o -o bin -lncurses -L/lib/SFML-2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
		rm *.o 
test.o: test.cpp
		$(CC) $(CFLAGS) test.cpp 
timeTests.o: timeTests.cpp
		$(CC) $(CFLAGS) timeTests.cpp 
main.o: main.cpp
		$(CC) $(CFLAGS) main.cpp 
UI.o: UI.cpp
		$(CC) $(CFLAGS) UI.cpp 
plotting.o: plotting.cpp
		$(CC) $(CFLAGS) plotting.cpp -I/lib/SFML-2.6.1/include
clean: 
		rm *.o

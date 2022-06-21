CC=g++

all: bot.exe

bot.exe: cursor.o board.o trie.h bot.cpp
	$(CC) -I. bot.cpp cursor.o board.o -o bot.exe

cursor.o: cursor.h cursor.cpp
	$(CC) -I. -c cursor.cpp -o cursor.o

board.o: board.h board.cpp
	$(CC) -I. -c board.cpp -o board.o

clean:
	del *.o *.exe
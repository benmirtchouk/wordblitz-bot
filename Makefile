CC=g++

all: bot.exe

bot.exe: trie.o cursor.o board.o trie.o bot.cpp
	$(CC) -I. bot.cpp trie.o cursor.o board.o -o bot.exe

trie.o: trie.h trie.cpp
	$(CC) -I. -c trie.cpp -o trie.o

cursor.o: cursor.h cursor.cpp
	$(CC) -I. -c cursor.cpp -o cursor.o

board.o: board.h board.cpp
	$(CC) -I. -c board.cpp -o board.o

clean:
	del *.o *.exe
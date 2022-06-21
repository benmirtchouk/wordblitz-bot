CC=g++

all: bot

bot: cursor.o trie.h bot.cpp
	$(CC) -I. bot.cpp cursor.o -o bot.exe

cursor.o: cursor.h cursor.cpp
	$(CC) -I. -c cursor.cpp -o cursor.o

clean:
	del *.o *.exe
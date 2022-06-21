# wordblitz-bot
A bot to play messenger's word blitz game [Example](https://www.youtube.com/watch?v=HU22wyLdopw)

## Build
Use `make` (recommended) or compile each component separately:
```sh
g++ -g -std=c++17 -I. -c trie.cpp -o trie.o
g++ -g -std=c++17 -I. -c cursor.cpp -o cursor.o
g++ -g -std=c++17 -I. -c board.cpp -o board.o
g++ -g -std=c++17 -I. bot.cpp trie.o cursor.o board.o -o bot.exe
```

## Run
After running `bot.exe` you will need to select the board area (top left and bottom right corners) by hovering over them and pressing `Q`. Then enter the board state as a single string of length 16 - reading off the letters from top to bottom and left to right.

To stop entering words after starting, hold the `E` key or terminate the process.
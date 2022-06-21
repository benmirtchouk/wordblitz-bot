#include <cursor.h>
#include <trie.h>
#include <board.h>
#include <Windows.h>

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

int main() {
  std::shared_ptr<TrieNode<char>> root = TrieNode<char>::create("wordlist.txt");
  Cursor cursor;
  Board board;

  std::vector<Board::path> paths = board.search(root);

  cursor.focus("Chrome_WidgetWin_1");
  Sleep(300);

  for(const Board::path& raw_path : paths) {
    if (GetKeyState('E') & 0x100) return 0;

    std::vector<std::pair<int, int>> path;
    std::transform(raw_path.cbegin(), raw_path.cend(), std::back_inserter(path), Board::decode);

    cursor.trace_path(path);
    Sleep(35);
  }

  return 0;
}

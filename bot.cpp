#include <cursor.h>
#include <trie.h>
#include <board.h>
#include <Windows.h>

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <memory>

int main() {
  std::shared_ptr<TrieNode<char>> root = TrieNode<char>::create("wordlist.txt");
  Cursor cursor;
  Board board;

  std::vector<Board::path> paths = board.search(root);

  cursor.focus("Chrome_WidgetWin_1");
  Sleep(300);

  std::unordered_set<std::string> entered_words;

  for(const Board::path& raw_path : paths) {
    if (GetKeyState('E') & 0x100) return 0;

    std::vector<std::pair<int, int>> path;
    std::string word;
    std::transform(raw_path.cbegin(), raw_path.cend(), std::back_inserter(path), Board::decode);
    std::transform(raw_path.cbegin(), raw_path.cend(), std::back_inserter(word), [&board](const int& index){ return board.get(index); });

    if (entered_words.insert(word).second) {
      std::cout << "Entering word: " << word << "\n";
      cursor.trace_path(path);
      Sleep(35);
    }
  }

  return 0;
}

#ifndef BOARD_H
#define BOARD_H

#include <trie.h>

#include <string>
#include <vector>
#include <unordered_set>
#include <memory>

class Board {
public:
  typedef std::vector<int> path;

  Board();
  std::vector<path> search(std::shared_ptr<TrieNode<char>> root) const;

  static int encode(int x, int y);
  static std::pair<int, int> decode(int index);

private:
  static const int SIZE;
  static const int dx[];
  static const int dy[];
  void search(int x, int y, std::shared_ptr<TrieNode<char>> node, path& cur_path, std::unordered_set<int>& visited, std::vector<path>& output) const;

  std::string d_letters;
};

#endif

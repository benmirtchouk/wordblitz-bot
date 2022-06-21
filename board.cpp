#include <board.h>

#include <iostream>
#include <cassert>
#include <algorithm>

const int Board::SIZE = 4;
const int Board::dx[8] = { -1, -1, -1, 0, 1, 1, 1, 0};
const int Board::dy[8] = { -1, 0, 1, 1, 1, 0, -1, -1};

Board::Board(): d_letters() {
  std::cout << "Board state? (input length " << Board::SIZE * Board::SIZE << " string)" << std::endl;
  std::string s;
  std::cin >> s;

  assert(s.size() == Board::SIZE * Board::SIZE);
  std::transform(s.cbegin(), s.cend(), std::back_inserter(d_letters), [](unsigned char c){ return std::tolower(c); });
}

int Board::encode(int x, int y) {
  return Board::SIZE * x + y;
}
std::pair<int, int> Board::decode(int index) {
  return { index / Board::SIZE, index % Board::SIZE };
}

std::vector<Board::path> Board::search(std::shared_ptr<TrieNode<char>> root) const {
  std::vector<Board::path> output;
  std::unordered_set<int> visited;
  Board::path cur_path;

  for (int i = 0; i < Board::SIZE; i++) {
    for (int j = 0; j < Board::SIZE; j++) {
      search(i, j, root, cur_path, visited, output);
    }
  }

  std::unordered_set<std::string> words;
  output.erase(
    std::remove_if(output.begin(), output.end(), [&](const Board::path& path) {
      std::string s;
      for (int i : path) s += d_letters[i];
      std::cout << "found word " << s << "\n";
      return !words.insert(s).second;
    }),
    output.end()
  );

  std::sort(output.begin(), output.end(), [](const Board::path & p1, const Board::path & p2) {
    return p1.size() > p2.size();
  });
  return output;
}

void Board::search(int x, int y, std::shared_ptr<TrieNode<char>> node, Board::path& cur_path, std::unordered_set<int>& visited, std::vector<Board::path>& output) const {
  int idx = encode(x, y);
  if (visited.find(idx) != visited.end()) return;
  node = node->traverse(d_letters[idx]);
  if (!node) return;

  cur_path.push_back(idx);
  visited.insert(idx);

  if (node->end()) {
    output.push_back(cur_path);
  }
  for(int d = 0; d < 8; d++) {
    int nx = x + Board::dx[d], ny = y + Board::dy[d];
    if (nx >= 0 && nx < Board::SIZE && ny >= 0 && ny < Board::SIZE) {
      search(nx, ny, node, cur_path, visited, output);
    }
  }

  visited.erase(idx);
  cur_path.pop_back();
}

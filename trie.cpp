#include <trie.h>

template <>
std::shared_ptr<TrieNode<char>> TrieNode<char>::create(const char* filename) {
  std::shared_ptr<TrieNode<char>> node = create();
  std::ifstream wordlist(filename);
  std::string word;
  while(wordlist >> word) {
    std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return std::tolower(c); });
    node->insert(word.begin(), word.end());
  }
  return node;
}
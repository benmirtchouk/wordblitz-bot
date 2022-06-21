#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>

template <typename K>
class TrieNode : public std::enable_shared_from_this<TrieNode<K>> {
  public:
    static std::shared_ptr<TrieNode<K>> create(bool end = false) {
      return std::shared_ptr<TrieNode<K>>(new TrieNode<K>(end));
    }

    bool end();
    std::shared_ptr<TrieNode<K>> traverse(const K& key);

    template <typename InputIt>
    void insert(InputIt first, InputIt last);

  private:
    TrieNode(bool end);

    bool d_end;
    std::unordered_map<K, std::shared_ptr<TrieNode>> d_edges;
};

template <typename K>
TrieNode<K>::TrieNode(bool end): d_end(end), d_edges() {}

template <typename K>
template <typename InputIt>
void TrieNode<K>::insert(InputIt first, InputIt last) {
  std::shared_ptr<TrieNode> node = this->shared_from_this();

  for (; first != last; ++first) {
    std::shared_ptr<TrieNode>& child = node->d_edges[*first];
    if (!child) child = TrieNode::create();
    node = child;
  }

  node->d_end = true;
}

template <typename K>
bool TrieNode<K>::end() { return d_end; }

template <typename K>
std::shared_ptr<TrieNode<K>> TrieNode<K>::traverse(const K& key) {
  auto it = d_edges.find(key);
  return it == d_edges.end() ? nullptr : it->second;
}

#endif
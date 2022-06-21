#include <Windows.h>
#include <bits/stdc++.h>
#include "cursor.cpp"
#include "trie.h"
#define all(a) a.begin(), a.end()
#define forn(i,n) for(int i = 0; i < (int) n; i++)

#define x first
#define y second
using namespace std;
typedef pair<int, int> pii;

vector<vector<char>> board(4, vector<char>(4));
string decode(vector<pii>& word) {
  string decoded = "";
  for(pii& p : word) decoded += board[p.x][p.y];
  return decoded;
}

void wait() {
  while(!(GetKeyState('Q') & 0x100));
}

int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0};
int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1};

int main() {
  /* board position */

  POINT tl, br;
  cout << "top left (press Q to mark)?\n";
  wait();
  GetCursorPos(&tl);
  Sleep(300);
  cout << "bottom right (press Q to mark)?\n";
  wait();
  GetCursorPos(&br);
  init(tl, br);

  /* board input */

  cout << "board state? (input length 16 string)\n";
  string s;
  cin >> s;
  assert(s.size() == 16);
  forn(i, 16) board[i / 4][i % 4] = (s[i] | ' ');

  /* wordlist input */

  ifstream wordlist("wordlist.txt");
  int n;
  wordlist >> n;
  shared_ptr<TrieNode<char>> root = TrieNode<char>::create();
  forn(i, n) {
    string word;
    wordlist >> word;
    root->insert(word.begin(), word.end());
  }

  /* get words */

  unordered_set<string> donewords;
  vector<vector<pii>> words;

  vector<vector<bool>> done(4, vector<bool>(4));
  function<void(std::shared_ptr<TrieNode<char>>, int, int, vector<pii>&)> dfs = [&](std::shared_ptr<TrieNode<char>> root, int x, int y, vector<pii>& word) {
    if (done[x][y]) return;
    if (!root) return;
    if (root->end()) {
      string decoded = decode(word);
      if (donewords.find(decoded) == donewords.end()) {
        donewords.insert(decoded);
        words.push_back(word);
        cout << "\t" << decoded << "\n";
      }
    }

    done[x][y] = 1;
    forn(d, 8) {
      int nx = x + dx[d], ny = y + dy[d];
      if (nx >= 0 && nx < 4 && ny >= 0 && ny < 4) {
        word.push_back({nx, ny});
        dfs(root->traverse(board[nx][ny]), nx, ny, word);
        word.pop_back();
      }
    }
    done[x][y] = 0;
  };

  forn(i, 4) forn(j, 4) {
    cout << "starting at " << i << ", " << j << "\n";
    vector<pii> word{{i, j}};
    dfs(root->traverse(board[i][j]), i, j, word);
  }

  /* input words */

  focus();
  Sleep(300);

  sort(all(words), [&](const vector<pii>& i, const vector<pii>& j) {
    return i.size() > j.size();
  });

  cout << "\n\n";

  for(vector<pii>& word : words) {
    if (GetKeyState('E') & 0x100) return 0;
    cout << decode(word) << "\n";
    input_word(word);
    Sleep(35);
  }
}

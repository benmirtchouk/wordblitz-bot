#include <Windows.h>
#include <bits/stdc++.h>
#include "cursor.cpp"
#define all(a) a.begin(), a.end()
#define forn(i,n) for(int i = 0; i < (int) n; i++)
#define ios ios::sync_with_stdio(false); cin.tie(0); cout.tie(0)

#define x first
#define y second
using namespace std;
typedef pair<int, int> pii;

// BEGIN TRIE //
struct trie {
  trie(bool e = false): endmarker(e), children( {
    0
  }) {}
  bool endmarker;
  trie* children[26];
};

bool insert(trie* root, string& s, int i = 0) {
  if (i == s.size() - 1)
    if(root->children[s[i]])
      if (root->children[s[i]]->endmarker)
        return false;
      else {
        root->children[s[i]]->endmarker = true;
        return true;
      }
    else {
      root->children[s[i]] = new trie(true);
      return true;
    }

  if (!root->children[s[i]])
    root->children[s[i]] = new trie();
  return insert(root->children[s[i]], s, i + 1);
}
// END TRIE //

void fix(string& s) {
  forn(i, s.size()) s[i] -= 'a';
}

vector<vector<int>> board(4, vector<int>(4));
string decode(vector<pii>& word) {
  string decoded = "";
  for(pii& p : word) decoded += board[p.x][p.y] + 'a';
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

  /* BOARD INPUT */

  cout << "board state? (input length 16 string)\n";
  string s;
  cin >> s;
  assert(s.size() == 16);
  forn(i, 16) board[i / 4][i % 4] = (s[i]|' ') - 'a';

  // WORDLIST INPUT

  ifstream wordlist("wordlist.txt");
  int n;
  wordlist >> n;
  trie *root = new trie();
  forn(i, n) {
    string word;
    wordlist >> word;
    fix(word);
    insert(root, word);
  }

  // GET WORDS

  unordered_set<string> donewords;
  vector<vector<pii>> words;

  vector<vector<bool>> done(4, vector<bool>(4));
  function<void(trie*, int, int, vector<pii>&)> dfs = [&](trie * root, int x, int y, vector<pii>& word) {
    if (done[x][y]) return;
    if (!root) return;
    if (root->endmarker) {

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
        dfs(root->children[board[nx][ny]], nx, ny, word);
        word.pop_back();
      }
    }
    done[x][y] = 0;
  };

  forn(i, 4) forn(j, 4) {
    cout << "starting at " << i << ", " << j << "\n";
    vector<pii> word{{i, j}};
    dfs(root->children[board[i][j]], i, j, word);
  }

  // INPUT WORDS

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
    Sleep(25);
  }
}

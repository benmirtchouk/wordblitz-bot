#include <Windows.h>
#include <bits/stdc++.h>
#define forn(i,n) for(int i = 0; i < (int) n; i++)

using namespace std;
typedef pair<int, int> pii;

int len, px, py;

void init(POINT tl, POINT br) {
  px = tl.x;
  py = tl.y;
  len = (br.x - tl.x) / 3;
  cout << "init with " << tl.x << " " << br.x << "\n";
}

bool focus() {
  HWND window = FindWindow("Chrome_WidgetWin_1", NULL);
  if (!window) {
    cout << "failed to grab window\n";
    return -1;
  }

  SetForegroundWindow(window);
  SetActiveWindow(window);
  SetFocus(window);

  return 0;
}

void startpath(int y, int x) {
  SetCursorPos(px + len * x, py + len * y);
  mouse_event(MOUSEEVENTF_LEFTDOWN, px + len * x, py + len * y, 0, 0);
}

void dragto(int y, int x) {
  SetCursorPos(px + len * x, py + len * y);
}

void endpath(int y, int x) {
  mouse_event(MOUSEEVENTF_LEFTUP, px + len * x, py + len * y, 0, 0);
}

void input_word(vector<pii>& path) {
  if (!path.size()) return;

  startpath(path[0].first, path[0].second);
  Sleep(35);

  for(int i = 1; i < path.size(); i++) {
    dragto(path[i].first, path[i].second);
    Sleep(35);
  }

  endpath(path.back().first, path.back().second);
}

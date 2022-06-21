#include <cursor.h>
#include <Windows.h>

#include <iostream>

Cursor::Cursor() {
  POINT tl, br;

  std::cout << "Top left (press Q to mark)?" << std::endl;
  while(!(GetKeyState('Q') & 0x100));
  GetCursorPos(&tl);

  Sleep(300);
  std::cout << "Bottom right (press Q to mark)?" << std::endl;
  while(!(GetKeyState('Q') & 0x100));
  GetCursorPos(&br);

  d_x = tl.x;
  d_y = tl.y;
  d_len = (br.x - tl.x) / 3;
}

void Cursor::focus(const char* windowName) {
  HWND window = FindWindow(windowName, NULL);
  if (window) {
    SetForegroundWindow(window);
    SetActiveWindow(window);
    SetFocus(window);
  }
}

void startpath(const std::pair<int, int>& pos) {
  SetCursorPos(pos.first, pos.second);
  mouse_event(MOUSEEVENTF_LEFTDOWN, pos.first, pos.second, 0, 0);
}
void dragto(const std::pair<int, int>& pos) {
  SetCursorPos(pos.first, pos.second);
}
void endpath(const std::pair<int, int>& pos) {
  mouse_event(MOUSEEVENTF_LEFTUP, pos.first, pos.second, 0, 0);
}

std::pair<int, int> Cursor::index_to_pixels(const std::pair<int, int>& index) {
  return { d_x + d_len * index.second, d_y + d_len * index.first };
}

void Cursor::trace_path(const std::vector<std::pair<int, int>>& path) {
  if (path.empty()) return;

  startpath(index_to_pixels(path[0]));
  Sleep(35);

  for(int i = 1; i < path.size(); i++) {
    dragto(index_to_pixels(path[i]));
    Sleep(35);
  }

  endpath(index_to_pixels(path.back()));
}


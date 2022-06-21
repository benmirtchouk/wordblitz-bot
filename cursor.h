#ifndef CURSOR_H
#define CURSOR_H

#include <Windows.h>
#include <vector>

class Cursor {
  public:
    Cursor();

    void focus(const char* windowName);
    void trace_path(const std::vector<std::pair<int,int>>& path);

  private:
    std::pair<int,int> index_to_pixels(const std::pair<int, int>& index);

    int d_x, d_y, d_len;
};

#endif
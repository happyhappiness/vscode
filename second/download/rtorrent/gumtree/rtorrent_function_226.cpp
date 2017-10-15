<typename A1, typename A2>
  void                print(int x, int y, char* str, A1 a1, A2 a2)            { mvwprintw(m_window, y, x, str, a1, a2); }
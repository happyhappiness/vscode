
  void        print_border(chtype ls, chtype rs,
			   chtype ts, chtype bs,
			   chtype tl, chtype tr,
			   chtype bl, chtype br)               { wborder(m_window, ls, rs, ts, bs, tl, tr, bl, br); }

  // The format string is non-const, but that will not be a problem
  // since the string shall always be a C string choosen at
  // compiletime. Might cause extra copying of the string?

  void print(int x, int y, char* str)                          { mvwprintw(m_window, y, x, str); }

  template <typename A1>
  void print(int x, int y, char* str, A1 a1)                   { mvwprintw(m_window, y, x, str, a1); }

  template <typename A1, typename A2>
  void print(int x, int y, char* str, A1 a1, A2 a2)            { mvwprintw(m_window, y, x, str, a1, a2); }

  template <typename A1, typename A2, typename A3>
  void print(int x, int y, char* str,
		  A1 a1, A2 a2, A3 a3)                         { mvwprintw(m_window, y, x, str, a1, a2, a3); }

  template <typename A1, typename A2, typename A3, typename A4>
  void print(int x, int y, char* str,
		  A1 a1, A2 a2, A3 a3, A4 a4)                  { mvwprintw(m_window, y, x, str, a1, a2, a3, a4); }

  template <typename A1, typename A2, typename A3, typename A4, typename A5>
  void print(int x, int y, char* str,
		  A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)           { mvwprintw(m_window, y, x, str, a1, a2, a3, a4, a5); }

  template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
  void print(int x, int y, char* str,
		  A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)    { mvwprintw(m_window, y, x, str, a1, a2, a3, a4, a5, a6); }

  void set_attr(int x, int y, int n, int attr, int color)      { mvwchgat(m_window, y, x, n, attr, color, NULL); }

  // Initialize stdscr.
  static void init();

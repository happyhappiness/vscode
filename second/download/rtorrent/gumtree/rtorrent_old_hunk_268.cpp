                                   chtype bl, chtype br)                      { wborder(m_window, ls, rs, ts, bs, tl, tr, bl, br); }

  // The format string is non-const, but that will not be a problem
  // since the string shall always be a C string choosen at
  // compiletime. Might cause extra copying of the string?

  void                print(unsigned int x, unsigned int y, const char* str, ...);

  void                print_attributes(unsigned int x, unsigned int y, const char* first, const char* last, const attributes_list* attributes);

  void                print_char(const chtype ch)                                 { waddch(m_window, ch); }
  void                print_char(unsigned int x, unsigned int y, const chtype ch) { mvwaddch(m_window, y, x, ch); }

  void                set_attr(unsigned int x, unsigned int y, unsigned int n, int attr, int color) { mvwchgat(m_window, y, x, n, attr, color, NULL); }

  // Initialize stdscr.
  static void         initialize();
  static void         cleanup();

  static int          get_screen_width()                                      { int x, y; getmaxyx(stdscr, y, x); return x; }
  static int          get_screen_height()                                     { int x, y; getmaxyx(stdscr, y, x); return y; }

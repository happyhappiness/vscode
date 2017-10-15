
  static bool         m_isInitialized;

  WINDOW*             m_window;
};

inline void
Canvas::print(unsigned int x, unsigned int y, const char* str, ...) {
  va_list arglist;

  va_start(arglist, str);
  wmove(m_window, y, x);
  vw_printw(m_window, const_cast<char*>(str), arglist);
  va_end(arglist);
}

}

#endif

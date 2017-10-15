
  static bool         m_isInitialized;

  WINDOW*             m_window;
};

// Undefines 'timeout' that ncurses defines which screws up the global
// namespace. Idiots; Especially you, ESR.
#undef timeout

}

#endif

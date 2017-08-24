(!default_vt100) {
    const char** t = 0;
    const char* term = getenv("TERM");
    if (term) {
      for (t = kwsysTerminalVT100Names; *t && strcmp(term, *t) != 0; ++t) {
      }
    }
    if (!(t && *t)) {
      return 0;
    }
  }
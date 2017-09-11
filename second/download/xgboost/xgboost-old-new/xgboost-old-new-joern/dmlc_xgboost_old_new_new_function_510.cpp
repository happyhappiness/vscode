inline void ParseStrML(char tok[]) {
    int i = 0;
    while ((ch_buf = this->GetChar()) != EOF) {
      switch (ch_buf) {
        case '\\': tok[i++] = this->GetChar(); break;
        case '\'': tok[i++] = '\0'; return;
        default: tok[i++] = ch_buf;
      }
    }
    Error("unterminated string");
  }
inline void ParseStr(char tok[]) {
    int i = 0;
    while ((ch_buf = this->GetChar()) != EOF) {
      switch (ch_buf) {
        case '\\': tok[i++] = this->GetChar(); break;
        case '\"': tok[i++] = '\0'; return;
        case '\r':
        case '\n': Error("ConfigReader: unterminated string");
        default: tok[i++] = ch_buf;
      }
    }
    Error("ConfigReader: unterminated string");
  }
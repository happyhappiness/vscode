
 private:
  char ch_buf;
  char s_name[100000], s_val[100000], s_buf[100000];

  inline void SkipLine(void) {
    do {
      ch_buf = this->GetChar();
    } while (ch_buf != EOF && ch_buf != '\n' && ch_buf != '\r');
  }

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
  // return newline
  inline bool GetNextToken(char tok[]) {
    int i = 0;
    bool new_line = false;
    while (ch_buf != EOF) {
      switch (ch_buf) {
        case '#' : SkipLine(); new_line = true; break;
        case '\"':
          if (i == 0) {
            ParseStr(tok); ch_buf = this->GetChar(); return new_line;
          } else {
            Error("ConfigReader: token followed directly by string");
          }
        case '\'':
          if (i == 0) {
            ParseStrML( tok ); ch_buf = this->GetChar(); return new_line;
          } else {
            Error("ConfigReader: token followed directly by string");
          }
        case '=':
          if (i == 0) {
            ch_buf = this->GetChar();
            tok[0] = '=';
            tok[1] = '\0';
          } else {
            tok[i] = '\0';
          }
          return new_line;
        case '\r':
        case '\n':
          if (i == 0) new_line = true;
        case '\t':
        case ' ' :
          ch_buf = this->GetChar();
          if (i > 0) {
            tok[i] = '\0';
            return new_line;
          }
          break;
        default:
          tok[i++] = ch_buf;
          ch_buf = this->GetChar();
          break;
      }
    }
    return true;
  }
};
/*!

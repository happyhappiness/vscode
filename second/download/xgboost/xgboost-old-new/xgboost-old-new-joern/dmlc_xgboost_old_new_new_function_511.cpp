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
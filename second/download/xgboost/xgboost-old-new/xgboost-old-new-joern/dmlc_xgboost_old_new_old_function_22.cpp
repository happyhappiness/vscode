inline bool GetNextToken(std::string *tok) {
    tok->clear();
    bool new_line = false;
    while (ch_buf != EOF) {
      switch (ch_buf) {
        case '#' : SkipLine(); new_line = true; break;
        case '\"':
          if (tok->length() == 0) {
            ParseStr(tok); ch_buf = this->GetChar(); return new_line;
          } else {
            Error("ConfigReader: token followed directly by string");
          }
        case '\'':
          if (tok->length() == 0) {
            ParseStrML(tok); ch_buf = this->GetChar(); return new_line;
          } else {
            Error("ConfigReader: token followed directly by string");
          }
        case '=':
          if (tok->length() == 0) {
            ch_buf = this->GetChar();
            *tok = '=';
          }
          return new_line;
        case '\r':
        case '\n':
          if (tok->length() == 0) new_line = true;
        case '\t':
        case ' ' :
          ch_buf = this->GetChar();
          if (tok->length() != 0) return new_line;
          break;
        default:
          *tok += ch_buf;
          ch_buf = this->GetChar();
          break;
      }
    }
    if (tok->length() == 0) {
      return true;
    } else {
      return false;
    }
  }
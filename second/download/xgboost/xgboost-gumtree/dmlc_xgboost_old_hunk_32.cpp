        case '\\': *tok += this->GetChar(); break;
        case '\"': return;
        case '\r':
        case '\n': Error("ConfigReader: unterminated string");
        default: *tok += ch_buf;
      }
    }
    Error("ConfigReader: unterminated string");
  }
  inline void ParseStrML(std::string *tok) {
    while ((ch_buf = this->GetChar()) != EOF) {

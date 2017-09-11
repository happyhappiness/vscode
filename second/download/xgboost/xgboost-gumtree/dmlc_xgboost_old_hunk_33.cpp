        default: *tok += ch_buf;
      }
    }
    Error("unterminated string");
  }
  // return newline
  inline bool GetNextToken(std::string *tok) {

        default: *tok += ch_buf;
      }
    }
    LOG(FATAL) << "unterminated string";
  }
  // return newline
  inline bool GetNextToken(std::string *tok) {

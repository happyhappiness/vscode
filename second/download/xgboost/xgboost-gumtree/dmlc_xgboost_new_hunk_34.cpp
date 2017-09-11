          if (tok->length() == 0) {
            ParseStr(tok); ch_buf = this->GetChar(); return new_line;
          } else {
            LOG(FATAL) << "ConfigReader: token followed directly by string";
          }
        case '\'':
          if (tok->length() == 0) {
            ParseStrML(tok); ch_buf = this->GetChar(); return new_line;
          } else {
            LOG(FATAL) << "ConfigReader: token followed directly by string";
          }
        case '=':
          if (tok->length() == 0) {

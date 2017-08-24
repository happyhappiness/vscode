((*ptr >= 0x20 && *ptr <= 0x7F) || *ptr == '\n' || *ptr == '\r' ||
        *ptr == '\t') {
      text_count++;
    }
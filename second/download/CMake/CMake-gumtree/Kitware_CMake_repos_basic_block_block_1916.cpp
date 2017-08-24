(size_t i = buffer.size() - 1; i > 0; i--) {
    if (buffer[i] == ' ' || buffer[i] == '\t') {
      break;
    }
    if (buffer[i] != '\n' && buffer[i] != '\r') {
      std::string val = value;
      value = buffer[i];
      value += val;
    }
  }
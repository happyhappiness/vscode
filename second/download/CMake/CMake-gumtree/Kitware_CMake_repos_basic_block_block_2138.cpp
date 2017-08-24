{
    std::string result = "";
    char lastch = 1;
    for (const char* ch = ret.c_str(); *ch != '\0'; ++ch) {
      // if it is already escaped then don't try to escape it again
      if ((*ch == ' ') && lastch != '\\') {
        result += '\\';
      }
      result += *ch;
      lastch = *ch;
    }
    ret = result;
  }
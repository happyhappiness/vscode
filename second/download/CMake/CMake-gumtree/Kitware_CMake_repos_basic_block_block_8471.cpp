{
    document_ += *iter;
    if (*iter == '\n' && *(iter + 1) == '/')
      writeIndent();
    ++iter;
  }
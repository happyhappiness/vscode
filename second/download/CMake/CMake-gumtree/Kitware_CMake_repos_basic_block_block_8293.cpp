{
    if (!(*current_ >= '0' && *current_ <= '9') &&
        !in(*current_, '.', 'e', 'E', '+', '-'))
      break;
    ++current_;
  }
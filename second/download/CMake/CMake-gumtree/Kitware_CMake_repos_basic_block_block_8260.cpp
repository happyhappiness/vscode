(; begin < end; ++begin)
    if (*begin == '\n' || *begin == '\r')
      return true;
{
      // if it is already escaped then don't try to escape it again
      if ((*ch == ' ') && lastch != '\\') {
        result += '\\';
      }
      result += *ch;
      lastch = *ch;
    }
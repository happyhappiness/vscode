{
    char c = *current++;
    if (c == '\r') // mac or dos EOL
    {
      if (*current == '\n') // convert dos EOL
        ++current;
      normalized += '\n';
    } else // handle unix EOL & other char
      normalized += c;
  }
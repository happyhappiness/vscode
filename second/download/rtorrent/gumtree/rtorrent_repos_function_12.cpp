inline char
hexchar_to_value(char c) {
  if (c >= '0' && c <= '9')
    return c - '0';

  else if (c >= 'A' && c <= 'F')
    return 10 + c - 'A';
    
  else
    return 10 + c - 'a';
}
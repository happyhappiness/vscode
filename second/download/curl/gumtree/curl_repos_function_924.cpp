static int get_char(char c, int base)
{
#ifndef NO_RANGE_TEST
  int value = -1;
  if(c <= '9' && c >= '0') {
    value = c - '0';
  }
  else if(c <= 'Z' && c >= 'A') {
    value = c - 'A' + 10;
  }
  else if(c <= 'z' && c >= 'a') {
    value = c - 'a' + 10;
  }
#else
  const char * cp;
  int value;

  cp = memchr(valchars, c, 10 + 26 + 26);

  if(!cp)
    return -1;

  value = cp - valchars;

  if(value >= 10 + 26)
    value -= 26;                /* Lowercase. */
#endif

  if(value >= base) {
    value = -1;
  }

  return value;
}
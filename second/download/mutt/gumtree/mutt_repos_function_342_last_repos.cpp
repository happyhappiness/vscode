static int parse_keycode (const char *s)
{
  char *endChar;
  long int result = strtol(s+1, &endChar, 8);
  /* allow trailing whitespace, eg.  < 1001 > */
  while (ISSPACE(*endChar))
    ++endChar;
  /* negative keycodes don't make sense, also detect overflow */
  if (*endChar != '>' || result < 0 || result == LONG_MAX) {
    return -1;
  }

  return result;
}
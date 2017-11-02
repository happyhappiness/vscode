static size_t copySubstring(char * to, const char * from)
{
  size_t i;

  /* Copy at most 64-characters, terminate with a newline and returns the
     effective number of stored characters. */

  for(i = 0; i < 64; i++) {
    to[i] = *from;
    if(!*from++)
      break;
  }

  to[i++] = '\n';
  return i;
}
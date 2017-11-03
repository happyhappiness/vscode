static inline char* ascii_strlower (char *s)
{
  char *p = s;

  while (*p)
  {
    *p = ascii_tolower ((unsigned int) *p);
    p++;
  }

  return s;
}
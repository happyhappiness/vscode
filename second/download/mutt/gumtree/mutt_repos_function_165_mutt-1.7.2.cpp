char *mutt_strlower (char *s)
{
  char *p = s;

  while (*p)
  {
    *p = tolower ((unsigned char) *p);
    p++;
  }

  return (s);
}
char *mutt_strlower (char *s)
{
  char *p = s;

  while (*p)
  {
    *p = tolower (*p);
    p++;
  }

  return (s);
}
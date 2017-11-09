static char *
rstrip_in_place(char *s)
{
  char *p;

  p = &s[strlen(s)];
  if (p == s)
    return s;
  p--;
  while (p >= s && (*p == '\n' || *p == '\r'))
    *p-- = '\0';
  return s;
}
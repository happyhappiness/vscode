int ascii_strncasecmp (const char *a, const char *b, int n)
{
  int i, j;
  
  if (a == b)
    return 0;
  if (a == NULL && b)
    return -1;
  if (b == NULL && a)
    return 1;
  
  for (j = 0; (*a || *b) && j < n; a++, b++, j++)
  {
    if ((i = ascii_tolower (*a) - ascii_tolower (*b)))
      return i;
  }
  
  return 0;
}
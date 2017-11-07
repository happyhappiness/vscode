int ascii_strcasecmp (const char *a, const char *b)
{
  int i;
  
  if (a == b)
    return 0;
  if (a == NULL && b)
    return -1;
  if (b == NULL && a)
    return 1;
  
  for (; *a || *b; a++, b++)
  {
    if ((i = ascii_tolower (*a) - ascii_tolower (*b)))
      return i;
  }
  
  return 0;
}
int strncasecmp (char *s1, char *s2, size_t n)
{
  register int c1, c2, l = 0;
  
  while (*s1 && *s2 && l < n)
  {
    c1 = tolower ((unsigned char) *s1);
    c2 = tolower ((unsigned char) *s2);
    if (c1 != c2)
      return (c1 - c2);
    s1++;
    s2++;
    l++;
  }
  if (l == n)
    return (int) (0);
  else
    return (int) (*s1 - *s2);
}
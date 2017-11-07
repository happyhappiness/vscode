int strcasecmp (char *s1, char *s2)
{
  register int c1, c2;
  
  while (*s1 && *s2)
  {
    c1 = tolower ((unsigned char) *s1);
    c2 = tolower ((unsigned char) *s2);
    if (c1 != c2)
      return (c1 - c2);
    s1++;
    s2++;
  }                                                                           
  return (int) (*s1 - *s2);
}
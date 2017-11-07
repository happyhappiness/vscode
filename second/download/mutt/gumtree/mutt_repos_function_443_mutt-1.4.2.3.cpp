int hash_string (const unsigned char *s, int n)
{
  int h = 0;

#if 0
  while (*s)
    h += *s++;
#else
  while (*s)
    h += (h << 7) + *s++;
  h = (h * SOMEPRIME) % n;
  h = (h >= 0) ? h : h + n;
#endif

  return (h % n);
}
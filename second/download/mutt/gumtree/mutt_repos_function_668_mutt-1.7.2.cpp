static unsigned int hash_string (const unsigned char *s, unsigned int n)
{
  unsigned int h = 0;

  while (*s)
    h += (h << 7) + *s++;
  h = (h * SOMEPRIME) % n;

  return h;
}
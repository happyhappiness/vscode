static unsigned int gen_string_hash (union hash_key key, unsigned int n)
{
  unsigned int h = 0;
  unsigned char *s = (unsigned char *)key.strkey;

  while (*s)
    h += (h << 7) + *s++;
  h = (h * SOMEPRIME) % n;

  return h;
}
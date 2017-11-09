static unsigned int gen_case_string_hash (union hash_key key, unsigned int n)
{
  unsigned int h = 0;
  unsigned char *s = (unsigned char *)key.strkey;

  while (*s)
    h += (h << 7) + tolower (*s++);
  h = (h * SOMEPRIME) % n;

  return h;
}
static unsigned long
hash_str(const char *key, size_t key_length)
{
  char *end = (char *) key + key_length;
  unsigned long h = 5381;

  while (key < end) {
    h += h << 5;
    h ^= (unsigned long) *key++;
  }

  return h;
}
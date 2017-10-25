static int
hash_key_compare(char *key1, size_t key1_len, char *key2, size_t key2_len)
{
  if (key1_len == key2_len &&
      *key1 == *key2 &&
      memcmp(key1, key2, key1_len) == 0) {
    return 1;
  }

  return 0;
}
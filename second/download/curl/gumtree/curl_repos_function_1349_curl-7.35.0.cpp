size_t Curl_str_key_compare(void*k1, size_t key1_len, void*k2, size_t key2_len)
{
  char *key1 = (char *)k1;
  char *key2 = (char *)k2;

  if(key1_len == key2_len &&
      *key1 == *key2 &&
      memcmp(key1, key2, key1_len) == 0) {
    return 1;
  }

  return 0;
}
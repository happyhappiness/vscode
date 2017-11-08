size_t Curl_str_key_compare(void *k1, size_t key1_len,
                            void *k2, size_t key2_len)
{
  if((key1_len == key2_len) && !memcmp(k1, k2, key1_len))
    return 1;

  return 0;
}
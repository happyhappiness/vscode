{
  if((key1_len == key2_len) && !memcmp(k1, k2, key1_len))
    return 1;

  return 0;
}
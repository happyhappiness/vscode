static struct curl_hash_element *
mk_hash_element(const void *key, size_t key_len, const void *p)
{
  struct curl_hash_element *he = malloc(sizeof(struct curl_hash_element));

  if(he) {
    void *dupkey = malloc(key_len);
    if(dupkey) {
      /* copy the key */
      memcpy(dupkey, key, key_len);

      he->key = dupkey;
      he->key_len = key_len;
      he->ptr = (void *) p;
    }
    else {
      /* failed to duplicate the key, free memory and fail */
      free(he);
      he = NULL;
    }
  }
  return he;
}
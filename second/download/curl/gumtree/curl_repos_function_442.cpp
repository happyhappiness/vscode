static struct curl_hash_element *
mk_hash_element(char *key, size_t key_len, const void *p)
{
  struct curl_hash_element *he =
    (struct curl_hash_element *) malloc(sizeof(struct curl_hash_element));

  if(he) {
    char *dup = strdup(key);
    if(dup) {
      he->key = dup;
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
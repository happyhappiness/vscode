static int
_mk_hash_element (curl_hash_element **e, char *key, size_t key_len,
                  const void *p)
{
  *e = (curl_hash_element *) malloc(sizeof(curl_hash_element));
  (*e)->key = strdup(key);
  (*e)->key_len = key_len;
  (*e)->ptr = (void *) p;
  return 0;
}
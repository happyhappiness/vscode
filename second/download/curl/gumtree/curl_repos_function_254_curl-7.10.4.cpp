int 
Curl_hash_add (curl_hash *h, char *key, size_t key_len, const void *p)
{
  curl_hash_element  *he;
  curl_llist_element *le;
  FETCH_LIST;

  for (le = CURL_LLIST_HEAD(l);
       le != NULL;
       le = CURL_LLIST_NEXT(le)) {
    he = (curl_hash_element *) CURL_LLIST_VALP(le);
    if (_hash_key_compare(he->key, he->key_len, key, key_len)) {
      h->dtor(he->ptr);
      he->ptr = (void *) p;
      return 1;
    }
  }

  if (_mk_hash_element(&he, key, key_len, p) != 0) 
    return 0;

  if (Curl_llist_insert_next(l, CURL_LLIST_TAIL(l), he)) {
    ++h->size;
    return 1;
  }

  return 0;
}
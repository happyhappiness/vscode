int 
Curl_hash_delete(curl_hash *h, char *key, size_t key_len)
{
  curl_hash_element  *he;
  curl_llist_element *le;
  FETCH_LIST;

  for (le = CURL_LLIST_HEAD(l);
       le != NULL;
       le = CURL_LLIST_NEXT(le)) {
    he = CURL_LLIST_VALP(le);
    if (_hash_key_compare(he->key, he->key_len, key, key_len)) {
      Curl_llist_remove(l, le, (void *) h);
      --h->size;
      return 1;
    }
  }

  return 0;
}
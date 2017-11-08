void *
Curl_hash_pick(curl_hash *h, char *key, size_t key_len)
{
  curl_llist_element *le;
  curl_hash_element  *he;
  FETCH_LIST;

  for (le = CURL_LLIST_HEAD(l);
       le != NULL;
       le = CURL_LLIST_NEXT(le)) {
    he = CURL_LLIST_VALP(le);
    if (_hash_key_compare(he->key, he->key_len, key, key_len)) {
      return he->ptr;
    }
  }

  return NULL;
}
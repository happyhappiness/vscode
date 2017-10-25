void *
Curl_hash_pick(struct curl_hash *h, char *key, size_t key_len)
{
  struct curl_llist_element *le;
  struct curl_hash_element  *he;
  struct curl_llist *l = FETCH_LIST(h, key, key_len);

  for (le = l->head;
       le;
       le = le->next) {
    he = le->ptr;
    if (hash_key_compare(he->key, he->key_len, key, key_len)) {
      return he->ptr;
    }
  }

  return NULL;
}
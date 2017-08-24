{
  struct curl_llist_element *le;
  struct curl_hash_element  *he;
  struct curl_llist *l;

  if(h) {
    l = FETCH_LIST(h, key, key_len);
    for(le = l->head; le; le = le->next) {
      he = le->ptr;
      if(h->comp_func(he->key, he->key_len, key, key_len)) {
        return he->ptr;
      }
    }
  }

  return NULL;
}
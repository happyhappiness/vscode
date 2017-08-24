{
  struct curl_hash_element  *he;
  struct curl_llist_element *le;
  struct curl_llist *l = FETCH_LIST(h, key, key_len);

  for(le = l->head; le; le = le->next) {
    he = (struct curl_hash_element *) le->ptr;
    if(h->comp_func(he->key, he->key_len, key, key_len)) {
      Curl_llist_remove(l, le, (void *)h);
      --h->size;
      break;
    }
  }

  he = mk_hash_element(key, key_len, p);
  if(he) {
    Curl_llist_insert_next(l, l->tail, he, &he->list);
    ++h->size;
    return p; /* return the new entry */
  }

  return NULL; /* failure */
}
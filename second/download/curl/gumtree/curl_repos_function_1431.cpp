void *
Curl_hash_add(struct curl_hash *h, void *key, size_t key_len, void *p)
{
  struct curl_hash_element  *he;
  struct curl_llist_element *le;
  struct curl_llist *l = FETCH_LIST (h, key, key_len);

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
    if(Curl_llist_insert_next(l, l->tail, he)) {
      ++h->size;
      return p; /* return the new entry */
    }
    /*
     * Couldn't insert it, destroy the 'he' element and the key again. We
     * don't call hash_element_dtor() since that would also call the
     * "destructor" for the actual data 'p'. When we fail, we shall not touch
     * that data.
     */
    free(he->key);
    free(he);
  }

  return NULL; /* failure */
}
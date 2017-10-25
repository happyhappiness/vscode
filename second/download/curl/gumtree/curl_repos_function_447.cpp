void
Curl_hash_clean_with_criterium(struct curl_hash *h, void *user,
                               int (*comp)(void *, void *))
{
  struct curl_llist_element *le;
  struct curl_llist_element *lnext;
  struct curl_llist *list;
  int i;

  for (i = 0; i < h->slots; ++i) {
    list = h->table[i];
    le = list->head; /* get first list entry */
    while(le) {
      struct curl_hash_element *he = le->ptr;
      lnext = le->next;
      /* ask the callback function if we shall remove this entry or not */
      if (comp(user, he->ptr)) {
        Curl_llist_remove(list, le, (void *) h);
        --h->size; /* one less entry in the hash now */
      }
      le = lnext;
    }
  }
}
void
Curl_hash_clean_with_criterium(curl_hash *h, void *user,
                               int (*comp)(void *, void *))
{
  curl_llist_element *le;
  curl_llist_element *lnext;
  int i;

  for (i = 0; i < h->slots; ++i) {
    le = CURL_LLIST_HEAD(h->table[i]);
    while(le != NULL)
      if (comp(user, ((curl_hash_element *) CURL_LLIST_VALP(le))->ptr)) {
        lnext = CURL_LLIST_NEXT(le);
        Curl_llist_remove(h->table[i], le, (void *) h);
        --h->size;
        le = lnext;
      }
      else
        le = CURL_LLIST_NEXT(le);
  }
}
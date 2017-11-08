void 
Curl_hash_apply(curl_hash *h, void *user,
                void (*cb)(void *user, void *ptr))
{
  curl_llist_element  *le;
  int                  i;

  for (i = 0; i < h->slots; ++i) {
    for (le = CURL_LLIST_HEAD(h->table[i]);
         le != NULL;
         le = CURL_LLIST_NEXT(le)) {
      curl_hash_element *el = CURL_LLIST_VALP(le);
      cb(user, el->ptr);
    }
  }
}
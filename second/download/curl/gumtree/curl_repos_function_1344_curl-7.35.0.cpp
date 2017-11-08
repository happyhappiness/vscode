void
Curl_hash_apply(curl_hash *h, void *user,
                void (*cb)(void *user, void *ptr))
{
  struct curl_llist_element  *le;
  int                  i;

  for(i = 0; i < h->slots; ++i) {
    for(le = (h->table[i])->head;
        le;
        le = le->next) {
      curl_hash_element *el = le->ptr;
      cb(user, el->ptr);
    }
  }
}
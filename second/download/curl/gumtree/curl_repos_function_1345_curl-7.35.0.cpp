void
Curl_hash_clean(struct curl_hash *h)
{
  int i;

  for(i = 0; i < h->slots; ++i) {
    Curl_llist_destroy(h->table[i], (void *) h);
    h->table[i] = NULL;
  }

  Curl_safefree(h->table);
  h->size = 0;
  h->slots = 0;
}
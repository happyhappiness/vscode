void
Curl_hash_clean(struct curl_hash *h)
{
  int i;

  for (i = 0; i < h->slots; ++i) {
    Curl_llist_destroy(h->table[i], (void *) h);
  }

  free(h->table);
}
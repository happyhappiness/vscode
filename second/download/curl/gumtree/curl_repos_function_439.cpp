int
Curl_hash_init(struct curl_hash *h, int slots, curl_hash_dtor dtor)
{
  int i;

  h->dtor = dtor;
  h->size = 0;
  h->slots = slots;

  h->table = (struct curl_llist **) malloc(slots * sizeof(struct curl_llist *));
  if(h->table) {
    for (i = 0; i < slots; ++i) {
      h->table[i] = Curl_llist_alloc((curl_llist_dtor) hash_element_dtor);
      if(!h->table[i]) {
        while(i--)
          Curl_llist_destroy(h->table[i], NULL);
        free(h->table);
        return 1; /* failure */
      }
    }
    return 0; /* fine */
  }
  else
    return 1; /* failure */
}
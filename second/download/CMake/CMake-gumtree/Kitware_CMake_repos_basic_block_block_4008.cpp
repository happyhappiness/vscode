{
  int i;

  if(!slots || !hfunc || !comparator ||!dtor) {
    return 1; /* failure */
  }

  h->hash_func = hfunc;
  h->comp_func = comparator;
  h->dtor = dtor;
  h->size = 0;
  h->slots = slots;

  h->table = malloc(slots * sizeof(struct curl_llist));
  if(h->table) {
    for(i = 0; i < slots; ++i)
      Curl_llist_init(&h->table[i], (curl_llist_dtor) hash_element_dtor);
    return 0; /* fine */
  }
  h->slots = 0;
  return 1; /* failure */
}
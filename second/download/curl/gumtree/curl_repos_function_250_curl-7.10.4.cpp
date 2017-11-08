void 
Curl_hash_init (curl_hash *h, int slots, curl_hash_dtor dtor)
{
  int i;

  h->dtor = dtor;
  h->size = 0;
  h->slots = slots;  

  h->table = (curl_llist **) malloc(slots * sizeof(curl_llist *));
  for (i = 0; i < slots; ++i) {
    h->table[i] = Curl_llist_alloc((curl_llist_dtor) _hash_element_dtor);
  }
}
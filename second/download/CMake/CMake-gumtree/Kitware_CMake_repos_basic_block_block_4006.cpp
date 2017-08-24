r(i = 0; i < slots; ++i)
      Curl_llist_init(&h->table[i], (curl_llist_dtor) hash_element_dtor)
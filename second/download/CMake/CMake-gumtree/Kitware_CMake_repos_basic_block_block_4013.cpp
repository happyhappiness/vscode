f(h->comp_func(he->key, he->key_len, key, key_len)) {
      Curl_llist_remove(l, le, (void *) h);
      --h->size;
      return 0;
    }
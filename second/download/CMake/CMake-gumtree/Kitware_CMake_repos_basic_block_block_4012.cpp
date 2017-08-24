{
      Curl_llist_remove(l, le, (void *) h);
      --h->size;
      return 0;
    }
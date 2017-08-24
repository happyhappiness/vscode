{
        Curl_llist_remove(list, le, (void *) h);
        --h->size; /* one less entry in the hash now */
      }
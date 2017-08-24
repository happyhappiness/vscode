{
      struct blacklist_node *n;
      size_t len = strlen(*servers);

      n = malloc(sizeof(struct blacklist_node) + len);
      if(!n) {
        Curl_llist_destroy(list, NULL);
        return CURLM_OUT_OF_MEMORY;
      }
      strcpy(n->server_name, *servers);

      Curl_llist_insert_next(list, list->tail, n->server_name,
                             &n->list);
      servers++;
    }
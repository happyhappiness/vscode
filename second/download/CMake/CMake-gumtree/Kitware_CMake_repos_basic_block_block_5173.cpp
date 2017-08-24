{
  /* Free the old list */
  if(list->size)
    Curl_llist_destroy(list, NULL);

  if(servers) {
    Curl_llist_init(list, (curl_llist_dtor) server_blacklist_llist_dtor);

    /* Parse the URLs and populate the list */
    while(*servers) {
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
  }


  return CURLM_OK;
}
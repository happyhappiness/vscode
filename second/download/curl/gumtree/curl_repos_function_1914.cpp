CURLMcode Curl_pipeline_set_site_blacklist(char **sites,
                                           struct curl_llist **list_ptr)
{
  struct curl_llist *old_list = *list_ptr;
  struct curl_llist *new_list = NULL;

  if(sites) {
    new_list = Curl_llist_alloc((curl_llist_dtor) site_blacklist_llist_dtor);
    if(!new_list)
      return CURLM_OUT_OF_MEMORY;

    /* Parse the URLs and populate the list */
    while(*sites) {
      char *hostname;
      char *port;
      struct site_blacklist_entry *entry;

      hostname = strdup(*sites);
      if(!hostname) {
        Curl_llist_destroy(new_list, NULL);
        return CURLM_OUT_OF_MEMORY;
      }

      entry = malloc(sizeof(struct site_blacklist_entry));
      if(!entry) {
        free(hostname);
        Curl_llist_destroy(new_list, NULL);
        return CURLM_OUT_OF_MEMORY;
      }

      port = strchr(hostname, ':');
      if(port) {
        *port = '\0';
        port++;
        entry->port = (unsigned short)strtol(port, NULL, 10);
      }
      else {
        /* Default port number for HTTP */
        entry->port = 80;
      }

      entry->hostname = hostname;

      if(!Curl_llist_insert_next(new_list, new_list->tail, entry)) {
        site_blacklist_llist_dtor(NULL, entry);
        Curl_llist_destroy(new_list, NULL);
        return CURLM_OUT_OF_MEMORY;
      }

      sites++;
    }
  }

  /* Free the old list */
  if(old_list) {
    Curl_llist_destroy(old_list, NULL);
  }

  /* This might be NULL if sites == NULL, i.e the blacklist is cleared */
  *list_ptr = new_list;

  return CURLM_OK;
}
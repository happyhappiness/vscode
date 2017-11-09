CURLMcode Curl_pipeline_set_site_blacklist(char **sites,
                                           struct curl_llist *list)
{
  /* Free the old list */
  if(list->size)
    Curl_llist_destroy(list, NULL);

  if(sites) {
    Curl_llist_init(list, (curl_llist_dtor) site_blacklist_llist_dtor);

    /* Parse the URLs and populate the list */
    while(*sites) {
      char *port;
      struct site_blacklist_entry *entry;

      entry = malloc(sizeof(struct site_blacklist_entry) + strlen(*sites));
      if(!entry) {
        Curl_llist_destroy(list, NULL);
        return CURLM_OUT_OF_MEMORY;
      }
      strcpy(entry->hostname, *sites);

      port = strchr(entry->hostname, ':');
      if(port) {
        *port = '\0';
        port++;
        entry->port = (unsigned short)strtol(port, NULL, 10);
      }
      else {
        /* Default port number for HTTP */
        entry->port = 80;
      }

      Curl_llist_insert_next(list, list->tail, entry, &entry->list);
      sites++;
    }
  }

  return CURLM_OK;
}
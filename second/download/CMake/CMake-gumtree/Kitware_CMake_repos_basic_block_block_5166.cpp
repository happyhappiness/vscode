e(*sites) {
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
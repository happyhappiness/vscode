CURLMcode Curl_pipeline_set_server_blacklist(char **servers,
                                             struct curl_llist **list_ptr)
{
  struct curl_llist *old_list = *list_ptr;
  struct curl_llist *new_list = NULL;

  if(servers) {
    new_list = Curl_llist_alloc((curl_llist_dtor) server_blacklist_llist_dtor);
    if(!new_list)
      return CURLM_OUT_OF_MEMORY;

    /* Parse the URLs and populate the list */
    while(*servers) {
      char *server_name;

      server_name = strdup(*servers);
      if(!server_name) {
        Curl_llist_destroy(new_list, NULL);
        return CURLM_OUT_OF_MEMORY;
      }

      if(!Curl_llist_insert_next(new_list, new_list->tail, server_name)) {
        Curl_llist_destroy(new_list, NULL);
        Curl_safefree(server_name);
        return CURLM_OUT_OF_MEMORY;
      }

      servers++;
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
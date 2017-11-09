bool Curl_pipeline_server_blacklisted(struct Curl_easy *handle,
                                      char *server_name)
{
  if(handle->multi && server_name) {
    struct curl_llist *list =
      Curl_multi_pipelining_server_bl(handle->multi);

    struct curl_llist_element *e = list->head;
    while(e) {
      struct blacklist_node *bl = (struct blacklist_node *)e;
      if(strncasecompare(bl->server_name, server_name,
                         strlen(bl->server_name))) {
        infof(handle, "Server %s is blacklisted\n", server_name);
        return TRUE;
      }
      e = e->next;
    }

    DEBUGF(infof(handle, "Server %s is not blacklisted\n", server_name));
  }
  return FALSE;
}
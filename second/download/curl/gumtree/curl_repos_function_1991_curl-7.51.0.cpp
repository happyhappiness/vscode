bool Curl_pipeline_server_blacklisted(struct Curl_easy *handle,
                                      char *server_name)
{
  if(handle->multi && server_name) {
    struct curl_llist *blacklist =
      Curl_multi_pipelining_server_bl(handle->multi);

    if(blacklist) {
      struct curl_llist_element *curr;

      curr = blacklist->head;
      while(curr) {
        char *bl_server_name;

        bl_server_name = curr->ptr;
        if(strncasecompare(bl_server_name, server_name,
                           strlen(bl_server_name))) {
          infof(handle, "Server %s is blacklisted\n", server_name);
          return TRUE;
        }
        curr = curr->next;
      }
    }

    DEBUGF(infof(handle, "Server %s is not blacklisted\n", server_name));
  }
  return FALSE;
}
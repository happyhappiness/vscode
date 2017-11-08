bool Curl_pipeline_site_blacklisted(struct Curl_easy *handle,
                                    struct connectdata *conn)
{
  if(handle->multi) {
    struct curl_llist *blacklist =
      Curl_multi_pipelining_site_bl(handle->multi);

    if(blacklist) {
      struct curl_llist_element *curr;

      curr = blacklist->head;
      while(curr) {
        struct site_blacklist_entry *site;

        site = curr->ptr;
        if(strcasecompare(site->hostname, conn->host.name) &&
           site->port == conn->remote_port) {
          infof(handle, "Site %s:%d is pipeline blacklisted\n",
                conn->host.name, conn->remote_port);
          return TRUE;
        }
        curr = curr->next;
      }
    }
  }
  return FALSE;
}
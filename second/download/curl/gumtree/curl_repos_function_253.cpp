CURLcode Curl_second_connect(struct connectdata *conn)
{
  CURLcode status = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct connectdata *sec_conn = NULL;   /* secondary connection */
  bool backup_reuse_fresh = data->set.reuse_fresh;
  char *backup_userpwd = data->set.userpwd;

  if(data->change.url_alloc)
    free(data->change.url);

  data->change.url_alloc = FALSE;
  data->change.url = data->set.source_url;

  /* We must never actually alter 'data->set' properties, so we restore the
     backed up values afterwards! */

#if 0
  /* if both remote hosts are the same host - create new connection */
  if (strequal(conn->host.dispname, data->set.source_host))
#endif
    data->set.reuse_fresh = TRUE;

  data->set.userpwd = data->set.source_userpwd;

  /* secondary connection */
  status = Curl_connect_host(data, &sec_conn);
  if(CURLE_OK == status) {
    sec_conn->sec_conn = NULL;  /* important if re-using existing connection
                                   to prevent loop */
    sec_conn->data = data;
    conn->sec_conn = sec_conn;
  }

  data->set.reuse_fresh = backup_reuse_fresh;
  data->set.userpwd = backup_userpwd;

  return status;
}
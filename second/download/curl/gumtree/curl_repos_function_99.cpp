CURLcode curl_disconnect(CURLconnect *c_connect)
{
  struct connectdata *conn = c_connect;

  struct UrlData *data = conn->data;

  free(conn); /* free the connection oriented data */

  /* clean up the sockets and SSL stuff from the previous "round" */
  urlfree(data, FALSE);

  return CURLE_OK;
}
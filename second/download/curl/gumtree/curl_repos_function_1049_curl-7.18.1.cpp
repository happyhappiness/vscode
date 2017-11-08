static CURLcode telnet_done(struct connectdata *conn,
                                 CURLcode status, bool premature)
{
  struct TELNET *tn = (struct TELNET *)conn->data->state.proto.telnet;
  (void)status; /* unused */
  (void)premature; /* not used */

  curl_slist_free_all(tn->telnet_vars);

  free(conn->data->state.proto.telnet);
  conn->data->state.proto.telnet = NULL;

  return CURLE_OK;
}
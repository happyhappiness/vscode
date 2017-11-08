CURLcode Curl_telnet_done(struct connectdata *conn)
{
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;
  curl_slist_free_all(tn->telnet_vars);

  free(conn->proto.telnet);
  conn->proto.telnet = NULL;

  return CURLE_OK;
}
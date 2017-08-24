{
  struct TELNET *tn = (struct TELNET *)conn->data->req.protop;
  (void)status; /* unused */
  (void)premature; /* not used */

  if(!tn)
    return CURLE_OK;

  curl_slist_free_all(tn->telnet_vars);
  tn->telnet_vars = NULL;

  Curl_safefree(conn->data->req.protop);

  return CURLE_OK;
}
static CURLcode SetupConnection(struct connectdata *conn,
                                struct Curl_dns_entry *hostaddr,
                                bool *protocol_done)
{
  struct SessionHandle *data = conn->data;
  CURLcode result=CURLE_OK;

  Curl_pgrsTime(data, TIMER_NAMELOOKUP);

  if(conn->protocol & PROT_FILE) {
    /* There's nothing in this function to setup if we're only doing
       a file:// transfer */
    *protocol_done = TRUE;
    return result;
  }
  *protocol_done = FALSE; /* default to not done */

  /*************************************************************
   * Send user-agent to HTTP proxies even if the target protocol
   * isn't HTTP.
   *************************************************************/
  if((conn->protocol&PROT_HTTP) ||
     (data->change.proxy && *data->change.proxy)) {
    if(data->set.useragent) {
      Curl_safefree(conn->allocptr.uagent);
      conn->allocptr.uagent =
        aprintf("User-Agent: %s\015\012", data->set.useragent);
      if(!conn->allocptr.uagent)
        return CURLE_OUT_OF_MEMORY;
    }
  }

  conn->bytecount = 0;
  conn->headerbytecount = 0;

  if(CURL_SOCKET_BAD == conn->sock[FIRSTSOCKET]) {
    bool connected = FALSE;

    /* Connect only if not already connected! */
    result = ConnectPlease(conn, hostaddr, &connected);

    if(connected) {
      result = Curl_protocol_connect(conn, protocol_done);
      if(CURLE_OK == result)
        conn->bits.tcpconnect = TRUE;
    }
    else
      conn->bits.tcpconnect = FALSE;


    if(CURLE_OK != result)
      return result;
  }
  else {
    Curl_pgrsTime(data, TIMER_CONNECT); /* we're connected already */
    conn->bits.tcpconnect = TRUE;
    *protocol_done = TRUE;
    if(data->set.verbose)
      verboseconnect(conn);
  }

  conn->now = Curl_tvnow(); /* time this *after* the connect is done, we
                               set this here perhaps a second time */

#ifdef __EMX__
  /* 20000330 mgs
   * the check is quite a hack...
   * we're calling _fsetmode to fix the problem with fwrite converting newline
   * characters (you get mangled text files, and corrupted binary files when
   * you download to stdout and redirect it to a file). */

  if ((data->set.out)->_handle == NULL) {
    _fsetmode(stdout, "b");
  }
#endif

  return CURLE_OK;
}
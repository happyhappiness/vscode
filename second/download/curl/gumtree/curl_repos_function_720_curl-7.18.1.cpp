static CURLcode SetupConnection(struct connectdata *conn,
                                struct Curl_dns_entry *hostaddr,
                                bool *protocol_done)
{
  CURLcode result=CURLE_OK;
  struct SessionHandle *data = conn->data;

  Curl_pgrsTime(data, TIMER_NAMELOOKUP);

  if(conn->protocol & PROT_FILE) {
    /* There's nothing in this function to setup if we're only doing
       a file:// transfer */
    *protocol_done = TRUE;
    return result;
  }
  *protocol_done = FALSE; /* default to not done */

  /* set proxy_connect_closed to false unconditionally already here since it
     is used strictly to provide extra information to a parent function in the
     case of proxy CONNECT failures and we must make sure we don't have it
     lingering set from a previous invoke */
  conn->bits.proxy_connect_closed = FALSE;

  /*************************************************************
   * Set user-agent for HTTP
   *************************************************************/
  if((conn->protocol&PROT_HTTP) && data->set.str[STRING_USERAGENT]) {
    Curl_safefree(conn->allocptr.uagent);
    conn->allocptr.uagent =
      aprintf("User-Agent: %s\r\n", data->set.str[STRING_USERAGENT]);
    if(!conn->allocptr.uagent)
      return CURLE_OUT_OF_MEMORY;
  }

  data->req.headerbytecount = 0;

#ifdef CURL_DO_LINEEND_CONV
  data->state.crlf_conversions = 0; /* reset CRLF conversion counter */
#endif /* CURL_DO_LINEEND_CONV */

  for(;;) {
    /* loop for CURL_SERVER_CLOSED_CONNECTION */

    if(CURL_SOCKET_BAD == conn->sock[FIRSTSOCKET]) {
      bool connected = FALSE;

      /* Connect only if not already connected! */
      result = ConnectPlease(data, conn, hostaddr, &connected);

      if(connected) {
        result = Curl_protocol_connect(conn, protocol_done);
        if(CURLE_OK == result)
          conn->bits.tcpconnect = TRUE;
      }
      else
        conn->bits.tcpconnect = FALSE;

      /* if the connection was closed by the server while exchanging
         authentication informations, retry with the new set
         authentication information */
      if(conn->bits.proxy_connect_closed) {
        /* reset the error buffer */
        if(data->set.errorbuffer)
          data->set.errorbuffer[0] = '\0';
        data->state.errorbuf = FALSE;
        continue;
      }

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
    /* Stop the loop now */
    break;
  }

  conn->now = Curl_tvnow(); /* time this *after* the connect is done, we
                               set this here perhaps a second time */

#ifdef __EMX__
  /* 20000330 mgs
   * the check is quite a hack...
   * we're calling _fsetmode to fix the problem with fwrite converting newline
   * characters (you get mangled text files, and corrupted binary files when
   * you download to stdout and redirect it to a file). */

  if((data->set.out)->_handle == NULL) {
    _fsetmode(stdout, "b");
  }
#endif

  return CURLE_OK;
}
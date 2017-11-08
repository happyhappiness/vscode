CURLcode Curl_protocol_connect(struct connectdata *conn, bool *protocol_done)
{
  struct SessionHandle *data = conn->data;
  CURLcode result=CURLE_OK;

  *protocol_done = FALSE;

  if(conn->bits.tcpconnect && conn->bits.protoconnstart) {
    /* We already are connected, get back. This may happen when the connect
       worked fine in the first call, like when we connect to a local server
       or proxy. Note that we don't know if the protocol is actually done.

       Unless this protocol doesn't have any protocol-connect callback, as
       then we know we're done. */
    if(!conn->curl_connecting)
      *protocol_done = TRUE;

    return CURLE_OK;
  }

  if(!conn->bits.tcpconnect) {

    Curl_pgrsTime(data, TIMER_CONNECT); /* connect done */

    if(data->set.verbose)
      verboseconnect(conn);
  }

  if(!conn->bits.protoconnstart) {
    if(conn->curl_connect) {
      /* is there a protocol-specific connect() procedure? */

      /* Set start time here for timeout purposes in the connect procedure, it
         is later set again for the progress meter purpose */
      conn->now = Curl_tvnow();

      /* Call the protocol-specific connect function */
      result = conn->curl_connect(conn, protocol_done);
    }
    else
      *protocol_done = TRUE;

    /* it has started, possibly even completed but that knowledge isn't stored
       in this bit! */
    conn->bits.protoconnstart = TRUE;
  }

  return result; /* pass back status */
}
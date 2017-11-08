CURLcode Curl_protocol_connect(struct connectdata *conn,
                               struct Curl_dns_entry *hostaddr)
{
  struct SessionHandle *data = conn->data;
  CURLcode result=CURLE_OK;

  if(conn->bits.tcpconnect)
    /* We already are connected, get back. This may happen when the connect
       worked fine in the first call, like when we connect to a local server
       or proxy. */
    return CURLE_OK;

  Curl_pgrsTime(data, TIMER_CONNECT); /* connect done */

  if(data->set.verbose)
    verboseconnect(conn, hostaddr);

  if(conn->curl_connect) {
    /* is there a protocol-specific connect() procedure? */

    /* set start time here for timeout purposes in the
     * connect procedure, it is later set again for the
     * progress meter purpose */
    conn->now = Curl_tvnow();

    /* Call the protocol-specific connect function */
    result = conn->curl_connect(conn);
  }

  return result; /* pass back status */
}
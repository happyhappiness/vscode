CURLcode Curl_do(struct connectdata **connp)
{
  CURLcode result=CURLE_OK;
  struct connectdata *conn = *connp;
  struct SessionHandle *data=conn->data;

  conn->bits.do_more = FALSE; /* by default there's no curl_do_more() to use */

  if(conn->curl_do) {
    /* generic protocol-specific function pointer set in curl_connect() */
    result = conn->curl_do(conn);

    /* This was formerly done in transfer.c, but we better do it here */

    if((CURLE_SEND_ERROR == result) && conn->bits.reuse) {
      /* This was a re-use of a connection and we got a write error in the
       * DO-phase. Then we DISCONNECT this connection and have another attempt
       * to CONNECT and then DO again! The retry cannot possibly find another
       * connection to re-use, since we only keep one possible connection for
       * each.  */

      infof(data, "Re-used connection seems dead, get a new one\n");

      conn->bits.close = TRUE; /* enforce close of this connetion */
      result = Curl_done(conn);   /* we are so done with this */
      if(CURLE_OK == result) {
        /* Now, redo the connect and get a new connection */
        result = Curl_connect(data, connp);
        if(CURLE_OK == result)
          /* ... finally back to actually retry the DO phase */
          result = conn->curl_do(*connp);
      }
    }
  }
  return result;
}
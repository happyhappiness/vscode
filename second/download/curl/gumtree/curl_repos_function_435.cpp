CURLcode Curl_do(struct connectdata **connp, bool *done)
{
  CURLcode result=CURLE_OK;
  struct connectdata *conn = *connp;
  struct SessionHandle *data=conn->data;

  conn->bits.do_more = FALSE; /* by default there's no curl_do_more() to use */

  if(conn->curl_do) {
    /* generic protocol-specific function pointer set in curl_connect() */
    result = conn->curl_do(conn, done);

    /* This was formerly done in transfer.c, but we better do it here */

    if((CURLE_SEND_ERROR == result) && conn->bits.reuse) {
      /* This was a re-use of a connection and we got a write error in the
       * DO-phase. Then we DISCONNECT this connection and have another attempt
       * to CONNECT and then DO again! The retry cannot possibly find another
       * connection to re-use, since we only keep one possible connection for
       * each.  */

      infof(data, "Re-used connection seems dead, get a new one\n");

      conn->bits.close = TRUE; /* enforce close of this connection */
      result = Curl_done(&conn, result); /* we are so done with this */

      /* conn may no longer be a good pointer */

      if(CURLE_OK == result) {
        bool async;
        bool protocol_done = TRUE;

        /* Now, redo the connect and get a new connection */
        result = Curl_connect(data, connp, &async, &protocol_done);
        if(CURLE_OK == result) {
          /* We have connected or sent away a name resolve query fine */

          conn = *connp; /* setup conn to again point to something nice */
          if(async) {
            /* Now, if async is TRUE here, we need to wait for the name
               to resolve */
            result = Curl_wait_for_resolv(conn, NULL);
            if(result)
              return result;

            /* Resolved, continue with the connection */
            result = Curl_async_resolved(conn, &protocol_done);
            if(result)
              return result;
          }

          /* ... finally back to actually retry the DO phase */
          result = conn->curl_do(conn, done);
        }
      }
    }
  }
  return result;
}
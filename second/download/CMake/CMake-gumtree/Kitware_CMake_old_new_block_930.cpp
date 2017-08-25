f(-1 == conn->firstsocket) {
    /* Connect only if not already connected! */
    result = ConnectPlease(conn);
    if(CURLE_OK != result)
      return result;

    if(conn->curl_connect) {
      /* is there a connect() procedure? */

      /* set start time here for timeout purposes in the
       * connect procedure, it is later set again for the
       * progress meter purpose */
      conn->now = Curl_tvnow();

      /* Call the protocol-specific connect function */
      result = conn->curl_connect(conn);
      if(result != CURLE_OK)
        return result; /* pass back errors */
    }
  }
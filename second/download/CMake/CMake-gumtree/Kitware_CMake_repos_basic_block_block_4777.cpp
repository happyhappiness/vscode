{
    bool async;
    bool protocol_done = TRUE;

    /* Now, redo the connect and get a new connection */
    result = Curl_connect(data, connp, &async, &protocol_done);
    if(!result) {
      /* We have connected or sent away a name resolve query fine */

      conn = *connp; /* setup conn to again point to something nice */
      if(async) {
        /* Now, if async is TRUE here, we need to wait for the name
           to resolve */
        result = Curl_resolver_wait_resolv(conn, NULL);
        if(result)
          return result;

        /* Resolved, continue with the connection */
        result = Curl_async_resolved(conn, &protocol_done);
        if(result)
          return result;
      }
    }
  }
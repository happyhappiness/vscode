{
      conn->data = data;
      conn->bits.tcpconnect[FIRSTSOCKET] = TRUE; /* we are "connected */

      Curl_conncache_add_conn(data->state.conn_cache, conn);

      /*
       * Setup whatever necessary for a resumed transfer
       */
      result = setup_range(data);
      if(result) {
        DEBUGASSERT(conn->handler->done);
        /* we ignore the return code for the protocol-specific DONE */
        (void)conn->handler->done(conn, result, FALSE);
        goto out;
      }

      Curl_setup_transfer(conn, -1, -1, FALSE, NULL, /* no download */
                          -1, NULL); /* no upload */
    }
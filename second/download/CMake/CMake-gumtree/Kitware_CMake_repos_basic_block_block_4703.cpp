{
      /* Set the connection's owner correctly */
      conn_candidate->data = data;

      /* the winner gets the honour of being disconnected */
      (void)Curl_disconnect(conn_candidate, /* dead_connection */ FALSE);
    }
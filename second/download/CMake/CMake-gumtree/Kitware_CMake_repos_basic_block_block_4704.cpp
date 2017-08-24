{
    infof(data, "Connection cache is full, closing the oldest one.\n");

    conn_candidate = Curl_oldest_idle_connection(data);

    if(conn_candidate) {
      /* Set the connection's owner correctly */
      conn_candidate->data = data;

      /* the winner gets the honour of being disconnected */
      (void)Curl_disconnect(conn_candidate, /* dead_connection */ FALSE);
    }
  }
{
        /* Set the connection's owner correctly, then kill it */
        conn_candidate->data = data;
        (void)Curl_disconnect(conn_candidate, /* dead_connection */ FALSE);
      }
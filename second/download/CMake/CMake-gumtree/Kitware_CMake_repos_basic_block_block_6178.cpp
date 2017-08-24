{
      struct connectdata *conn_candidate;

      /* The bundle is full. Let's see if we can kill a connection. */
      conn_candidate = find_oldest_idle_connection_in_bundle(data, bundle);

      if(conn_candidate) {
        /* Set the connection's owner correctly, then kill it */
        conn_candidate->data = data;
        (void)Curl_disconnect(conn_candidate, /* dead_connection */ FALSE);
      }
      else {
        infof(data, "No more connections allowed to host: %d\n",
              max_host_connections);
        connections_available = FALSE;
      }
    }
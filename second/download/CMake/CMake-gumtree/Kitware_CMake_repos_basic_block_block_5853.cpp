{
      conn->data = data;
      infof(data, "Connection %ld seems to be dead!\n", conn->connection_id);

      /* disconnect resources */
      Curl_disconnect(conn, /* dead_connection */TRUE);
      return TRUE;
    }
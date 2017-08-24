{
      infof(conn->data, "http2_send: Warning: The cumulative length of all "
            "headers exceeds %zu bytes and that could cause the "
            "stream to be rejected.\n", MAX_ACC);
    }
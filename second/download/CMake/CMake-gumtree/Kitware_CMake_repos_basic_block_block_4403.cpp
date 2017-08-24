f(!conn->connect_buffer) {
      conn->connect_buffer = malloc(CONNECT_BUFFER_SIZE);
      if(!conn->connect_buffer)
        return CURLE_OUT_OF_MEMORY;
    }
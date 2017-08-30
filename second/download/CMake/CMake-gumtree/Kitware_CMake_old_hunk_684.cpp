
      host_port = aprintf("%s:%hu", hostname, remote_port);
      if(!host_port) {
        free(req_buffer);
        return CURLE_OUT_OF_MEMORY;
      }


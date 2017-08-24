{
    /* increase enc buffer in order to fit the requested amount of data */
    size = connssl->encdata_length - connssl->encdata_offset;
    if(size < CURL_SCHANNEL_BUFFER_FREE_SIZE ||
       connssl->encdata_length < min_encdata_length) {
      reallocated_length = connssl->encdata_offset +
                           CURL_SCHANNEL_BUFFER_FREE_SIZE;
      if(reallocated_length < min_encdata_length) {
        reallocated_length = min_encdata_length;
      }
      reallocated_buffer = realloc(connssl->encdata_buffer,
                                   reallocated_length);
      if(reallocated_buffer == NULL) {
        *err = CURLE_OUT_OF_MEMORY;
        failf(data, "schannel: unable to re-allocate memory");
        goto cleanup;
      }

      connssl->encdata_buffer = reallocated_buffer;
      connssl->encdata_length = reallocated_length;
      size = connssl->encdata_length - connssl->encdata_offset;
      infof(data, "schannel: encdata_buffer resized %zu\n",
            connssl->encdata_length);
    }

    infof(data, "schannel: encrypted data buffer: offset %zu length %zu\n",
          connssl->encdata_offset, connssl->encdata_length);

    /* read encrypted data from socket */
    *err = Curl_read_plain(conn->sock[sockindex],
                           (char *)(connssl->encdata_buffer +
                                    connssl->encdata_offset),
                           size, &nread);
    if(*err) {
      nread = -1;
      if(*err == CURLE_AGAIN)
        infof(data, "schannel: Curl_read_plain returned CURLE_AGAIN\n");
      else if(*err == CURLE_RECV_ERROR)
        infof(data, "schannel: Curl_read_plain returned CURLE_RECV_ERROR\n");
      else
        infof(data, "schannel: Curl_read_plain returned error %d\n", *err);
    }
    else if(nread == 0) {
      connssl->recv_connection_closed = true;
      infof(data, "schannel: server closed the connection\n");
    }
    else if(nread > 0) {
      connssl->encdata_offset += (size_t)nread;
      connssl->encdata_is_incomplete = false;
      infof(data, "schannel: encrypted data got %zd\n", nread);
    }
  }
{
    Curl_add_buffer_free(http->header_recvbuf);
    http->header_recvbuf = NULL; /* clear the pointer */
    Curl_add_buffer_free(http->trailer_recvbuf);
    http->trailer_recvbuf = NULL; /* clear the pointer */
    for(; http->push_headers_used > 0; --http->push_headers_used) {
      free(http->push_headers[http->push_headers_used - 1]);
    }
    free(http->push_headers);
    http->push_headers = NULL;
  }
{
    /* This is trailer fields. */
    /* 3 is for ":" and "\r\n". */
    uint32_t n = (uint32_t)(namelen + valuelen + 3);

    DEBUGF(infof(data_s, "h2 trailer: %.*s: %.*s\n", namelen, name, valuelen,
                 value));

    Curl_add_buffer(stream->trailer_recvbuf, &n, sizeof(n));
    Curl_add_buffer(stream->trailer_recvbuf, name, namelen);
    Curl_add_buffer(stream->trailer_recvbuf, ": ", 2);
    Curl_add_buffer(stream->trailer_recvbuf, value, valuelen);
    Curl_add_buffer(stream->trailer_recvbuf, "\r\n\0", 3);

    return 0;
  }
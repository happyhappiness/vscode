{
    DEBUGF(infof(conn->data, "http2_send: nothing to do in this session\n"));
    *err = CURLE_HTTP2;
    return -1;
  }
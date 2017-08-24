{
    DEBUGF(infof(data,
                 "http2_recv: nothing to do in this session\n"));
    *err = CURLE_HTTP2;
    return -1;
  }
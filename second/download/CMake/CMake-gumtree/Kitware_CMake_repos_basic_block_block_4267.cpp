f(stream_id < 0) {
    DEBUGF(infof(conn->data, "http2_send() send error\n"));
    *err = CURLE_SEND_ERROR;
    return -1;
  }
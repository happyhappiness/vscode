{
    failf(conn->data, "Failed sending HTTP2 data");
    return NGHTTP2_ERR_CALLBACK_FAILURE;
  }
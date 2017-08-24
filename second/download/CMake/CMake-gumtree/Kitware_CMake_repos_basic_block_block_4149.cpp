f(!stream) {
    DEBUGF(infof(conn->data, "No proto pointer for stream: %x\n",
                 stream_id));
    return NGHTTP2_ERR_CALLBACK_FAILURE;
  }
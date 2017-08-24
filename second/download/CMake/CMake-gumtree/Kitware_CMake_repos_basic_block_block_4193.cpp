{
    /* RST_STREAM */
    nghttp2_submit_rst_stream(httpc->h2, NGHTTP2_FLAG_NONE, http->stream_id,
                              NGHTTP2_STREAM_CLOSED);
    if(http->stream_id == httpc->pause_stream_id) {
      infof(data, "stopped the pause stream!\n");
      httpc->pause_stream_id = 0;
    }
  }
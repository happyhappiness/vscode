{
    /* stream 1 is opened implicitly on upgrade */
    stream->stream_id = 1;
    /* queue SETTINGS frame (again) */
    rv = nghttp2_session_upgrade(httpc->h2, httpc->binsettings,
                                 httpc->binlen, NULL);
    if(rv != 0) {
      failf(data, "nghttp2_session_upgrade() failed: %s(%d)",
            nghttp2_strerror(rv), rv);
      return CURLE_HTTP2;
    }

    nghttp2_session_set_stream_user_data(httpc->h2,
                                         stream->stream_id,
                                         conn->data);
  }
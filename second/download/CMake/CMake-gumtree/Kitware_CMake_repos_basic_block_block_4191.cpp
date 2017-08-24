{
    nghttp2_session_set_stream_user_data(httpc->h2, http->stream_id, 0);
    http->stream_id = 0;
  }
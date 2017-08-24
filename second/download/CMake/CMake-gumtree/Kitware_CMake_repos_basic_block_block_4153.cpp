{
    /* stream ID zero is for connection-oriented stuff */
    if(frame->hd.type == NGHTTP2_SETTINGS) {
      uint32_t max_conn = httpc->settings.max_concurrent_streams;
      DEBUGF(infof(conn->data, "Got SETTINGS\n"));
      httpc->settings.max_concurrent_streams =
        nghttp2_session_get_remote_settings(
          session, NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS);
      httpc->settings.enable_push =
        nghttp2_session_get_remote_settings(
          session, NGHTTP2_SETTINGS_ENABLE_PUSH);
      DEBUGF(infof(conn->data, "MAX_CONCURRENT_STREAMS == %d\n",
                   httpc->settings.max_concurrent_streams));
      DEBUGF(infof(conn->data, "ENABLE_PUSH == %s\n",
                   httpc->settings.enable_push?"TRUE":"false"));
      if(max_conn != httpc->settings.max_concurrent_streams) {
        /* only signal change if the value actually changed */
        infof(conn->data,
              "Connection state changed (MAX_CONCURRENT_STREAMS updated)!\n");
        Curl_multi_connchanged(conn->data->multi);
      }
    }
    return 0;
  }
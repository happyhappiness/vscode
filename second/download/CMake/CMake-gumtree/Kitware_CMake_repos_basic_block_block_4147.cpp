f(!stream->bodystarted) {
      rv = nghttp2_submit_rst_stream(session, NGHTTP2_FLAG_NONE,
                                     stream_id, NGHTTP2_PROTOCOL_ERROR);

      if(nghttp2_is_fatal(rv)) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
      }
    }
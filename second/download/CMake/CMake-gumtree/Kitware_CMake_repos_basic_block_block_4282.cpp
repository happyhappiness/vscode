{
    if(stream->close_handled) {
      infof(conn->data, "stream %d closed\n", stream->stream_id);
      *err = CURLE_HTTP2_STREAM;
      return -1;
    }
    else if(stream->closed) {
      return http2_handle_stream_close(conn, conn->data, stream, err);
    }
    /* If stream_id != -1, we have dispatched request HEADERS, and now
       are going to send or sending request body in DATA frame */
    stream->upload_mem = mem;
    stream->upload_len = len;
    nghttp2_session_resume_data(h2, stream->stream_id);
    rv = h2_session_send(conn->data, h2);
    if(nghttp2_is_fatal(rv)) {
      *err = CURLE_SEND_ERROR;
      return -1;
    }
    len -= stream->upload_len;

    /* Nullify here because we call nghttp2_session_send() and they
       might refer to the old buffer. */
    stream->upload_mem = NULL;
    stream->upload_len = 0;

    if(should_close_session(httpc)) {
      DEBUGF(infof(conn->data, "http2_send: nothing to do in this session\n"));
      *err = CURLE_HTTP2;
      return -1;
    }

    if(stream->upload_left) {
      /* we are sure that we have more data to send here.  Calling the
         following API will make nghttp2_session_want_write() return
         nonzero if remote window allows it, which then libcurl checks
         socket is writable or not.  See http2_perform_getsock(). */
      nghttp2_session_resume_data(h2, stream->stream_id);
    }

    DEBUGF(infof(conn->data, "http2_send returns %zu for stream %u\n", len,
                 stream->stream_id));
    return len;
  }
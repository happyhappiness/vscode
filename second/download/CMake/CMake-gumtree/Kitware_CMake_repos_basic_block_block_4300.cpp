{
  CURLcode result;
  struct http_conn *httpc = &conn->proto.httpc;
  int rv;
  ssize_t nproc;
  struct Curl_easy *data = conn->data;
  struct HTTP *stream = conn->data->req.protop;

  result = Curl_http2_setup(conn);
  if(result)
    return result;

  httpc->recv_underlying = (recving)conn->recv[FIRSTSOCKET];
  httpc->send_underlying = (sending)conn->send[FIRSTSOCKET];
  conn->recv[FIRSTSOCKET] = http2_recv;
  conn->send[FIRSTSOCKET] = http2_send;

  if(conn->data->req.upgr101 == UPGR101_RECEIVED) {
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
  else {
    populate_settings(conn, httpc);

    /* stream ID is unknown at this point */
    stream->stream_id = -1;
    rv = nghttp2_submit_settings(httpc->h2, NGHTTP2_FLAG_NONE,
                                 httpc->local_settings,
                                 httpc->local_settings_num);
    if(rv != 0) {
      failf(data, "nghttp2_submit_settings() failed: %s(%d)",
            nghttp2_strerror(rv), rv);
      return CURLE_HTTP2;
    }
  }

#ifdef NGHTTP2_HAS_SET_LOCAL_WINDOW_SIZE
  rv = nghttp2_session_set_local_window_size(httpc->h2, NGHTTP2_FLAG_NONE, 0,
                                             HTTP2_HUGE_WINDOW_SIZE);
  if(rv != 0) {
    failf(data, "nghttp2_session_set_local_window_size() failed: %s(%d)",
          nghttp2_strerror(rv), rv);
    return CURLE_HTTP2;
  }
#endif

  /* we are going to copy mem to httpc->inbuf.  This is required since
     mem is part of buffer pointed by stream->mem, and callbacks
     called by nghttp2_session_mem_recv() will write stream specific
     data into stream->mem, overwriting data already there. */
  if(H2_BUFSIZE < nread) {
    failf(data, "connection buffer size is too small to store data following "
                "HTTP Upgrade response header: buflen=%zu, datalen=%zu",
          H2_BUFSIZE, nread);
    return CURLE_HTTP2;
  }

  infof(conn->data, "Copying HTTP/2 data in stream buffer to connection buffer"
                    " after upgrade: len=%zu\n",
        nread);

  if(nread)
    memcpy(httpc->inbuf, mem, nread);
  httpc->inbuflen = nread;

  nproc = nghttp2_session_mem_recv(httpc->h2, (const uint8_t *)httpc->inbuf,
                                   httpc->inbuflen);

  if(nghttp2_is_fatal((int)nproc)) {
    failf(data, "nghttp2_session_mem_recv() failed: %s(%d)",
          nghttp2_strerror((int)nproc), (int)nproc);
    return CURLE_HTTP2;
  }

  DEBUGF(infof(data, "nghttp2_session_mem_recv() returns %zd\n", nproc));

  if((ssize_t)nread == nproc) {
    httpc->inbuflen = 0;
    httpc->nread_inbuf = 0;
  }
  else {
    httpc->nread_inbuf += nproc;
  }

  /* Try to send some frames since we may read SETTINGS already. */
  rv = h2_session_send(data, httpc->h2);

  if(rv != 0) {
    failf(data, "nghttp2_session_send() failed: %s(%d)",
          nghttp2_strerror(rv), rv);
    return CURLE_HTTP2;
  }

  if(should_close_session(httpc)) {
    DEBUGF(infof(data,
                 "nghttp2_session_send(): nothing to do in this session\n"));
    return CURLE_HTTP2;
  }

  return CURLE_OK;
}
CURLcode Curl_http2_switched(struct connectdata *conn,
                             const char *mem, size_t nread)
{
  CURLcode result;
  struct http_conn *httpc = &conn->proto.httpc;
  int rv;
  struct SessionHandle *data = conn->data;

  httpc->recv_underlying = (recving)conn->recv[FIRSTSOCKET];
  httpc->send_underlying = (sending)conn->send[FIRSTSOCKET];
  conn->recv[FIRSTSOCKET] = http2_recv;
  conn->send[FIRSTSOCKET] = http2_send;

  rv = (int) ((Curl_send*)httpc->send_underlying)
    (conn, FIRSTSOCKET,
     NGHTTP2_CLIENT_CONNECTION_PREFACE,
     NGHTTP2_CLIENT_CONNECTION_PREFACE_LEN,
     &result);
  if(result)
    /* TODO: This may get CURLE_AGAIN */
    return result;

  if(rv != 24) {
    failf(data, "Only sent partial HTTP2 packet");
    return CURLE_SEND_ERROR;
  }

  if(conn->data->req.upgr101 == UPGR101_RECEIVED) {
    /* stream 1 is opened implicitly on upgrade */
    httpc->stream_id = 1;
    /* queue SETTINGS frame (again) */
    rv = nghttp2_session_upgrade(httpc->h2, httpc->binsettings,
                                 httpc->binlen, NULL);
    if(rv != 0) {
      failf(data, "nghttp2_session_upgrade() failed: %s(%d)",
            nghttp2_strerror(rv), rv);
      return CURLE_HTTP2;
    }
  }
  else {
    /* stream ID is unknown at this point */
    httpc->stream_id = -1;
    rv = nghttp2_submit_settings(httpc->h2, NGHTTP2_FLAG_NONE, NULL, 0);
    if(rv != 0) {
      failf(data, "nghttp2_submit_settings() failed: %s(%d)",
            nghttp2_strerror(rv), rv);
      return CURLE_HTTP2;
    }
  }

  rv = (int)nghttp2_session_mem_recv(httpc->h2, (const uint8_t*)mem, nread);

  if(rv != (int)nread) {
    failf(data, "nghttp2_session_mem_recv() failed: %s(%d)",
          nghttp2_strerror(rv), rv);
    return CURLE_HTTP2;
  }

  return CURLE_OK;
}
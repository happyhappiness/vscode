static int h2_process_pending_input(struct Curl_easy *data,
                                    struct http_conn *httpc,
                                    CURLcode *err)
{
  ssize_t nread;
  char *inbuf;
  ssize_t rv;

  nread = httpc->inbuflen - httpc->nread_inbuf;
  inbuf = httpc->inbuf + httpc->nread_inbuf;

  rv = nghttp2_session_mem_recv(httpc->h2, (const uint8_t *)inbuf, nread);
  if(rv < 0) {
    failf(data,
          "h2_process_pending_input: nghttp2_session_mem_recv() returned "
          "%d:%s\n", rv, nghttp2_strerror((int)rv));
    *err = CURLE_RECV_ERROR;
    return -1;
  }

  if(nread == rv) {
    DEBUGF(infof(data,
                 "h2_process_pending_input: All data in connection buffer "
                 "processed\n"));
    httpc->inbuflen = 0;
    httpc->nread_inbuf = 0;
  }
  else {
    httpc->nread_inbuf += rv;
    DEBUGF(infof(data,
                 "h2_process_pending_input: %zu bytes left in connection "
                 "buffer\n",
                 httpc->inbuflen - httpc->nread_inbuf));
  }

  rv = h2_session_send(data, httpc->h2);
  if(rv != 0) {
    *err = CURLE_SEND_ERROR;
    return -1;
  }

  if(should_close_session(httpc)) {
    DEBUGF(infof(data,
                 "h2_process_pending_input: nothing to do in this session\n"));
    *err = CURLE_HTTP2;
    return -1;
  }

  return 0;
}
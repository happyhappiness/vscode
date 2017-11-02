static ssize_t http2_recv(struct connectdata *conn, int sockindex,
                          char *mem, size_t len, CURLcode *err)
{
  CURLcode result = CURLE_OK;
  ssize_t rv;
  ssize_t nread;
  struct http_conn *httpc = &conn->proto.httpc;

  (void)sockindex; /* we always do HTTP2 on sockindex 0 */

  if(httpc->closed) {
    /* Reset to FALSE to prevent infinite loop in readwrite_data
       function. */
    httpc->closed = FALSE;
    return 0;
  }

  /* Nullify here because we call nghttp2_session_send() and they
     might refer to the old buffer. */
  httpc->upload_mem = NULL;
  httpc->upload_len = 0;

  if(httpc->bodystarted &&
     httpc->nread_header_recvbuf < httpc->header_recvbuf->size_used) {
    size_t left =
      httpc->header_recvbuf->size_used - httpc->nread_header_recvbuf;
    size_t ncopy = len < left ? len : left;
    memcpy(mem, httpc->header_recvbuf->buffer + httpc->nread_header_recvbuf,
           ncopy);
    httpc->nread_header_recvbuf += ncopy;
    return ncopy;
  }

  if(httpc->data) {
    nread = len < httpc->datalen ? len : httpc->datalen;
    memcpy(mem, httpc->data, nread);

    httpc->data += nread;
    httpc->datalen -= nread;

    infof(conn->data, "%zu data written\n", nread);
    if(httpc->datalen == 0) {
      httpc->data = NULL;
      httpc->datalen = 0;
    }
    return nread;
  }

  conn->proto.httpc.mem = mem;
  conn->proto.httpc.len = len;

  infof(conn->data, "http2_recv: %d bytes buffer\n",
        conn->proto.httpc.len);

  nread = ((Curl_recv*)httpc->recv_underlying)(conn, FIRSTSOCKET,
                                               httpc->inbuf, H2_BUFSIZE,
                                               &result);
  if(result == CURLE_AGAIN) {
    *err = result;
    return -1;
  }

  if(nread == -1) {
    failf(conn->data, "Failed receiving HTTP2 data");
    *err = result;
    return 0;
  }

  infof(conn->data, "nread=%zd\n", nread);

  if(nread == 0) {
    failf(conn->data, "EOF");
    return 0;
  }

  rv = nghttp2_session_mem_recv(httpc->h2,
                                (const uint8_t *)httpc->inbuf, nread);

  if(nghttp2_is_fatal((int)rv)) {
    failf(conn->data, "nghttp2_session_mem_recv() returned %d:%s\n",
          rv, nghttp2_strerror((int)rv));
    *err = CURLE_RECV_ERROR;
    return 0;
  }
  infof(conn->data, "nghttp2_session_mem_recv() returns %zd\n", rv);
  /* Always send pending frames in nghttp2 session, because
     nghttp2_session_mem_recv() may queue new frame */
  rv = nghttp2_session_send(httpc->h2);
  if(rv != 0) {
    *err = CURLE_SEND_ERROR;
    return 0;
  }
  if(len != httpc->len) {
    return len - conn->proto.httpc.len;
  }
  /* If stream is closed, return 0 to signal the http routine to close
     the connection */
  if(httpc->closed) {
    /* Reset to FALSE to prevent infinite loop in readwrite_data
       function. */
    httpc->closed = FALSE;
    return 0;
  }
  *err = CURLE_AGAIN;
  return -1;
}
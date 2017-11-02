static int on_header(nghttp2_session *session, const nghttp2_frame *frame,
                     const uint8_t *name, size_t namelen,
                     const uint8_t *value, size_t valuelen,
                     uint8_t flags,
                     void *userp)
{
  struct connectdata *conn = (struct connectdata *)userp;
  struct http_conn *c = &conn->proto.httpc;
  int rv;
  int goodname;
  int goodheader;

  (void)session;
  (void)frame;
  (void)flags;

  /* Ignore PUSH_PROMISE for now */
  if(frame->hd.type != NGHTTP2_HEADERS) {
    return 0;
  }

  if(frame->hd.stream_id != c->stream_id) {
    return 0;
  }

  if(c->bodystarted) {
    /* Ignore trailer or HEADERS not mapped to HTTP semantics.  The
       consequence is handled in on_frame_recv(). */
    return 0;
  }

  goodname = nghttp2_check_header_name(name, namelen);
  goodheader = nghttp2_check_header_value(value, valuelen);

  if(!goodname || !goodheader) {

    infof(conn->data, "Detected bad incoming header %s%s, reset stream!\n",
          goodname?"":"name",
          goodheader?"":"value");

    rv = nghttp2_submit_rst_stream(session, NGHTTP2_FLAG_NONE,
                                   frame->hd.stream_id,
                                   NGHTTP2_PROTOCOL_ERROR);

    if(nghttp2_is_fatal(rv)) {
      return NGHTTP2_ERR_CALLBACK_FAILURE;
    }

    return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
  }

  if(namelen == sizeof(":status") - 1 &&
     memcmp(STATUS, name, namelen) == 0) {

    /* :status must appear exactly once. */
    if(c->status_code != -1 ||
       (c->status_code = decode_status_code(value, valuelen)) == -1) {

      rv = nghttp2_submit_rst_stream(session, NGHTTP2_FLAG_NONE,
                                     frame->hd.stream_id,
                                     NGHTTP2_PROTOCOL_ERROR);
      if(nghttp2_is_fatal(rv)) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
      }

      return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
    }

    Curl_add_buffer(c->header_recvbuf, "HTTP/2.0 ", 9);
    Curl_add_buffer(c->header_recvbuf, value, valuelen);
    Curl_add_buffer(c->header_recvbuf, "\r\n", 2);

    return 0;
  }
  else {
    /* Here we are sure that namelen > 0 because of
       nghttp2_check_header_name().  Pseudo header other than :status
       is illegal. */
    if(c->status_code == -1 || name[0] == ':') {
      rv = nghttp2_submit_rst_stream(session, NGHTTP2_FLAG_NONE,
                                     frame->hd.stream_id,
                                     NGHTTP2_PROTOCOL_ERROR);
      if(nghttp2_is_fatal(rv)) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
      }

      return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
    }

    /* convert to a HTTP1-style header */
    Curl_add_buffer(c->header_recvbuf, name, namelen);
    Curl_add_buffer(c->header_recvbuf, ":", 1);
    Curl_add_buffer(c->header_recvbuf, value, valuelen);
    Curl_add_buffer(c->header_recvbuf, "\r\n", 2);

    infof(conn->data, "got http2 header: %.*s: %.*s\n",
          namelen, name, valuelen, value);
  }

  return 0; /* 0 is successful */
}
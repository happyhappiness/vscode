static int on_frame_recv(nghttp2_session *session, const nghttp2_frame *frame,
                         void *userp)
{
  struct connectdata *conn = (struct connectdata *)userp;
  struct http_conn *c = &conn->proto.httpc;
  int rv;
  size_t left, ncopy;

  (void)session;
  (void)frame;
  infof(conn->data, "on_frame_recv() was called with header %x\n",
        frame->hd.type);
  switch(frame->hd.type) {
  case NGHTTP2_DATA:
    /* If body started, then receiving DATA is illegal. */
    if(!c->bodystarted) {
      rv = nghttp2_submit_rst_stream(session, NGHTTP2_FLAG_NONE,
                                     frame->hd.stream_id,
                                     NGHTTP2_PROTOCOL_ERROR);

      if(nghttp2_is_fatal(rv)) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
      }
    }
    break;
  case NGHTTP2_HEADERS:
    if(frame->headers.cat == NGHTTP2_HCAT_REQUEST)
      break;

    if(c->bodystarted) {
      /* Only valid HEADERS after body started is trailer header,
         which is not fully supported in this code.  If HEADERS is not
         trailer, then it is a PROTOCOL_ERROR. */
      if((frame->hd.flags & NGHTTP2_FLAG_END_STREAM) == 0) {
        rv = nghttp2_submit_rst_stream(session, NGHTTP2_FLAG_NONE,
                                       frame->hd.stream_id,
                                       NGHTTP2_PROTOCOL_ERROR);

        if(nghttp2_is_fatal(rv)) {
          return NGHTTP2_ERR_CALLBACK_FAILURE;
        }
      }
      break;
    }

    if(c->status_code == -1) {
      /* No :status header field means PROTOCOL_ERROR. */
      rv = nghttp2_submit_rst_stream(session, NGHTTP2_FLAG_NONE,
                                     frame->hd.stream_id,
                                     NGHTTP2_PROTOCOL_ERROR);

      if(nghttp2_is_fatal(rv)) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
      }

      break;
    }

    /* Only final status code signals the end of header */
    if(c->status_code / 100 != 1) {
      c->bodystarted = TRUE;
    }

    c->status_code = -1;

    Curl_add_buffer(c->header_recvbuf, "\r\n", 2);

    left = c->header_recvbuf->size_used - c->nread_header_recvbuf;
    ncopy = c->len < left ? c->len : left;

    memcpy(c->mem, c->header_recvbuf->buffer + c->nread_header_recvbuf, ncopy);
    c->nread_header_recvbuf += ncopy;

    c->mem += ncopy;
    c->len -= ncopy;
    break;
  case NGHTTP2_PUSH_PROMISE:
    rv = nghttp2_submit_rst_stream(session, NGHTTP2_FLAG_NONE,
                                   frame->push_promise.promised_stream_id,
                                   NGHTTP2_CANCEL);
    if(nghttp2_is_fatal(rv)) {
      return rv;
    }
    break;
  }
  return 0;
}
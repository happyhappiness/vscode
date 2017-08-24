{
  struct HTTP *stream;
  struct Curl_easy *data_s;
  int32_t stream_id = frame->hd.stream_id;
  struct connectdata *conn = (struct connectdata *)userp;
  (void)flags;

  DEBUGASSERT(stream_id); /* should never be a zero stream ID here */

  /* get the stream from the hash based on Stream ID */
  data_s = nghttp2_session_get_stream_user_data(session, stream_id);
  if(!data_s)
    /* Receiving a Stream ID not in the hash should not happen, this is an
       internal error more than anything else! */
    return NGHTTP2_ERR_CALLBACK_FAILURE;

  stream = data_s->req.protop;
  if(!stream) {
    failf(data_s, "Internal NULL stream! 5\n");
    return NGHTTP2_ERR_CALLBACK_FAILURE;
  }

  /* Store received PUSH_PROMISE headers to be used when the subsequent
     PUSH_PROMISE callback comes */
  if(frame->hd.type == NGHTTP2_PUSH_PROMISE) {
    char *h;

    if(!stream->push_headers) {
      stream->push_headers_alloc = 10;
      stream->push_headers = malloc(stream->push_headers_alloc *
                                    sizeof(char *));
      stream->push_headers_used = 0;
    }
    else if(stream->push_headers_used ==
            stream->push_headers_alloc) {
      char **headp;
      stream->push_headers_alloc *= 2;
      headp = Curl_saferealloc(stream->push_headers,
                               stream->push_headers_alloc * sizeof(char *));
      if(!headp) {
        stream->push_headers = NULL;
        return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
      }
      stream->push_headers = headp;
    }
    h = aprintf("%s:%s", name, value);
    if(h)
      stream->push_headers[stream->push_headers_used++] = h;
    return 0;
  }

  if(stream->bodystarted) {
    /* This is trailer fields. */
    /* 3 is for ":" and "\r\n". */
    uint32_t n = (uint32_t)(namelen + valuelen + 3);

    DEBUGF(infof(data_s, "h2 trailer: %.*s: %.*s\n", namelen, name, valuelen,
                 value));

    Curl_add_buffer(stream->trailer_recvbuf, &n, sizeof(n));
    Curl_add_buffer(stream->trailer_recvbuf, name, namelen);
    Curl_add_buffer(stream->trailer_recvbuf, ": ", 2);
    Curl_add_buffer(stream->trailer_recvbuf, value, valuelen);
    Curl_add_buffer(stream->trailer_recvbuf, "\r\n\0", 3);

    return 0;
  }

  if(namelen == sizeof(":status") - 1 &&
     memcmp(":status", name, namelen) == 0) {
    /* nghttp2 guarantees :status is received first and only once, and
       value is 3 digits status code, and decode_status_code always
       succeeds. */
    stream->status_code = decode_status_code(value, valuelen);
    DEBUGASSERT(stream->status_code != -1);

    Curl_add_buffer(stream->header_recvbuf, "HTTP/2 ", 7);
    Curl_add_buffer(stream->header_recvbuf, value, valuelen);
    /* the space character after the status code is mandatory */
    Curl_add_buffer(stream->header_recvbuf, " \r\n", 3);
    /* if we receive data for another handle, wake that up */
    if(conn->data != data_s)
      Curl_expire(data_s, 0, EXPIRE_RUN_NOW);

    DEBUGF(infof(data_s, "h2 status: HTTP/2 %03d (easy %p)\n",
                 stream->status_code, data_s));
    return 0;
  }

  /* nghttp2 guarantees that namelen > 0, and :status was already
     received, and this is not pseudo-header field . */
  /* convert to a HTTP1-style header */
  Curl_add_buffer(stream->header_recvbuf, name, namelen);
  Curl_add_buffer(stream->header_recvbuf, ": ", 2);
  Curl_add_buffer(stream->header_recvbuf, value, valuelen);
  Curl_add_buffer(stream->header_recvbuf, "\r\n", 2);
  /* if we receive data for another handle, wake that up */
  if(conn->data != data_s)
    Curl_expire(data_s, 0, EXPIRE_RUN_NOW);

  DEBUGF(infof(data_s, "h2 header: %.*s: %.*s\n", namelen, name, valuelen,
               value));

  return 0; /* 0 is successful */
}
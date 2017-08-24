{
  /*
   * BIG TODO: Currently, we send request in this function, but this
   * function is also used to send request body. It would be nice to
   * add dedicated function for request.
   */
  int rv;
  struct http_conn *httpc = &conn->proto.httpc;
  struct HTTP *stream = conn->data->req.protop;
  nghttp2_nv *nva = NULL;
  size_t nheader;
  size_t i;
  size_t authority_idx;
  char *hdbuf = (char *)mem;
  char *end, *line_end;
  nghttp2_data_provider data_prd;
  int32_t stream_id;
  nghttp2_session *h2 = httpc->h2;
  nghttp2_priority_spec pri_spec;

  (void)sockindex;

  DEBUGF(infof(conn->data, "http2_send len=%zu\n", len));

  if(stream->stream_id != -1) {
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

  /* Calculate number of headers contained in [mem, mem + len) */
  /* Here, we assume the curl http code generate *correct* HTTP header
     field block */
  nheader = 0;
  for(i = 1; i < len; ++i) {
    if(hdbuf[i] == '\n' && hdbuf[i - 1] == '\r') {
      ++nheader;
      ++i;
    }
  }
  if(nheader < 2)
    goto fail;

  /* We counted additional 2 \r\n in the first and last line. We need 3
     new headers: :method, :path and :scheme. Therefore we need one
     more space. */
  nheader += 1;
  nva = malloc(sizeof(nghttp2_nv) * nheader);
  if(nva == NULL) {
    *err = CURLE_OUT_OF_MEMORY;
    return -1;
  }

  /* Extract :method, :path from request line */
  line_end = strstr(hdbuf, "\r\n");

  /* Method does not contain spaces */
  end = memchr(hdbuf, ' ', line_end - hdbuf);
  if(!end || end == hdbuf)
    goto fail;
  nva[0].name = (unsigned char *)":method";
  nva[0].namelen = strlen((char *)nva[0].name);
  nva[0].value = (unsigned char *)hdbuf;
  nva[0].valuelen = (size_t)(end - hdbuf);
  nva[0].flags = NGHTTP2_NV_FLAG_NONE;
  if(HEADER_OVERFLOW(nva[0])) {
    failf(conn->data, "Failed sending HTTP request: Header overflow");
    goto fail;
  }

  hdbuf = end + 1;

  /* Path may contain spaces so scan backwards */
  end = NULL;
  for(i = (size_t)(line_end - hdbuf); i; --i) {
    if(hdbuf[i - 1] == ' ') {
      end = &hdbuf[i - 1];
      break;
    }
  }
  if(!end || end == hdbuf)
    goto fail;
  nva[1].name = (unsigned char *)":path";
  nva[1].namelen = strlen((char *)nva[1].name);
  nva[1].value = (unsigned char *)hdbuf;
  nva[1].valuelen = (size_t)(end - hdbuf);
  nva[1].flags = NGHTTP2_NV_FLAG_NONE;
  if(HEADER_OVERFLOW(nva[1])) {
    failf(conn->data, "Failed sending HTTP request: Header overflow");
    goto fail;
  }

  hdbuf = end + 1;

  end = line_end;
  nva[2].name = (unsigned char *)":scheme";
  nva[2].namelen = strlen((char *)nva[2].name);
  if(conn->handler->flags & PROTOPT_SSL)
    nva[2].value = (unsigned char *)"https";
  else
    nva[2].value = (unsigned char *)"http";
  nva[2].valuelen = strlen((char *)nva[2].value);
  nva[2].flags = NGHTTP2_NV_FLAG_NONE;
  if(HEADER_OVERFLOW(nva[2])) {
    failf(conn->data, "Failed sending HTTP request: Header overflow");
    goto fail;
  }

  authority_idx = 0;
  i = 3;
  while(i < nheader) {
    size_t hlen;

    hdbuf = line_end + 2;

    line_end = strstr(hdbuf, "\r\n");
    if(line_end == hdbuf)
      goto fail;

    /* header continuation lines are not supported */
    if(*hdbuf == ' ' || *hdbuf == '\t')
      goto fail;

    for(end = hdbuf; end < line_end && *end != ':'; ++end)
      ;
    if(end == hdbuf || end == line_end)
      goto fail;
    hlen = end - hdbuf;

    if(hlen == 4 && strncasecompare("host", hdbuf, 4)) {
      authority_idx = i;
      nva[i].name = (unsigned char *)":authority";
      nva[i].namelen = strlen((char *)nva[i].name);
    }
    else {
      nva[i].name = (unsigned char *)hdbuf;
      nva[i].namelen = (size_t)(end - hdbuf);
    }
    hdbuf = end + 1;
    while(*hdbuf == ' ' || *hdbuf == '\t')
      ++hdbuf;
    end = line_end;

    switch(inspect_header((const char *)nva[i].name, nva[i].namelen, hdbuf,
                          end - hdbuf)) {
    case HEADERINST_IGNORE:
      /* skip header fields prohibited by HTTP/2 specification. */
      --nheader;
      continue;
    case HEADERINST_TE_TRAILERS:
      nva[i].value = (uint8_t*)"trailers";
      nva[i].valuelen = sizeof("trailers") - 1;
      break;
    default:
      nva[i].value = (unsigned char *)hdbuf;
      nva[i].valuelen = (size_t)(end - hdbuf);
    }

    nva[i].flags = NGHTTP2_NV_FLAG_NONE;
    if(HEADER_OVERFLOW(nva[i])) {
      failf(conn->data, "Failed sending HTTP request: Header overflow");
      goto fail;
    }
    ++i;
  }

  /* :authority must come before non-pseudo header fields */
  if(authority_idx != 0 && authority_idx != AUTHORITY_DST_IDX) {
    nghttp2_nv authority = nva[authority_idx];
    for(i = authority_idx; i > AUTHORITY_DST_IDX; --i) {
      nva[i] = nva[i - 1];
    }
    nva[i] = authority;
  }

  /* Warn stream may be rejected if cumulative length of headers is too large.
     It appears nghttp2 will not send a header frame larger than 64KB. */
#define MAX_ACC 60000  /* <64KB to account for some overhead */
  {
    size_t acc = 0;

    for(i = 0; i < nheader; ++i) {
      acc += nva[i].namelen + nva[i].valuelen;

      DEBUGF(infof(conn->data, "h2 header: %.*s:%.*s\n",
                   nva[i].namelen, nva[i].name,
                   nva[i].valuelen, nva[i].value));
    }

    if(acc > MAX_ACC) {
      infof(conn->data, "http2_send: Warning: The cumulative length of all "
            "headers exceeds %zu bytes and that could cause the "
            "stream to be rejected.\n", MAX_ACC);
    }
  }

  h2_pri_spec(conn->data, &pri_spec);

  switch(conn->data->set.httpreq) {
  case HTTPREQ_POST:
  case HTTPREQ_POST_FORM:
  case HTTPREQ_PUT:
    if(conn->data->state.infilesize != -1)
      stream->upload_left = conn->data->state.infilesize;
    else
      /* data sending without specifying the data amount up front */
      stream->upload_left = -1; /* unknown, but not zero */

    data_prd.read_callback = data_source_read_callback;
    data_prd.source.ptr = NULL;
    stream_id = nghttp2_submit_request(h2, &pri_spec, nva, nheader,
                                       &data_prd, conn->data);
    break;
  default:
    stream_id = nghttp2_submit_request(h2, &pri_spec, nva, nheader,
                                       NULL, conn->data);
  }

  Curl_safefree(nva);

  if(stream_id < 0) {
    DEBUGF(infof(conn->data, "http2_send() send error\n"));
    *err = CURLE_SEND_ERROR;
    return -1;
  }

  infof(conn->data, "Using Stream ID: %x (easy handle %p)\n",
        stream_id, conn->data);
  stream->stream_id = stream_id;

  /* this does not call h2_session_send() since there can not have been any
   * priority upodate since the nghttp2_submit_request() call above */
  rv = nghttp2_session_send(h2);

  if(rv != 0) {
    *err = CURLE_SEND_ERROR;
    return -1;
  }

  if(should_close_session(httpc)) {
    DEBUGF(infof(conn->data, "http2_send: nothing to do in this session\n"));
    *err = CURLE_HTTP2;
    return -1;
  }

  if(stream->stream_id != -1) {
    /* If whole HEADERS frame was sent off to the underlying socket,
       the nghttp2 library calls data_source_read_callback. But only
       it found that no data available, so it deferred the DATA
       transmission. Which means that nghttp2_session_want_write()
       returns 0 on http2_perform_getsock(), which results that no
       writable socket check is performed. To workaround this, we
       issue nghttp2_session_resume_data() here to bring back DATA
       transmission from deferred state. */
    nghttp2_session_resume_data(h2, stream->stream_id);
  }

  return len;

fail:
  free(nva);
  *err = CURLE_SEND_ERROR;
  return -1;
}
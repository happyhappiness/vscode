{
  CURLcode result = CURLE_OK;
  ssize_t rv;
  ssize_t nread;
  struct http_conn *httpc = &conn->proto.httpc;
  struct Curl_easy *data = conn->data;
  struct HTTP *stream = data->req.protop;

  (void)sockindex; /* we always do HTTP2 on sockindex 0 */

  if(should_close_session(httpc)) {
    DEBUGF(infof(data,
                 "http2_recv: nothing to do in this session\n"));
    *err = CURLE_HTTP2;
    return -1;
  }

  /* Nullify here because we call nghttp2_session_send() and they
     might refer to the old buffer. */
  stream->upload_mem = NULL;
  stream->upload_len = 0;

  /*
   * At this point 'stream' is just in the Curl_easy the connection
   * identifies as its owner at this time.
   */

  if(stream->bodystarted &&
     stream->nread_header_recvbuf < stream->header_recvbuf->size_used) {
    /* If there is body data pending for this stream to return, do that */
    size_t left =
      stream->header_recvbuf->size_used - stream->nread_header_recvbuf;
    size_t ncopy = MIN(len, left);
    memcpy(mem, stream->header_recvbuf->buffer + stream->nread_header_recvbuf,
           ncopy);
    stream->nread_header_recvbuf += ncopy;

    DEBUGF(infof(data, "http2_recv: Got %d bytes from header_recvbuf\n",
                 (int)ncopy));
    return ncopy;
  }

  DEBUGF(infof(data, "http2_recv: easy %p (stream %u)\n",
               data, stream->stream_id));

  if((data->state.drain) && stream->memlen) {
    DEBUGF(infof(data, "http2_recv: DRAIN %zu bytes stream %u!! (%p => %p)\n",
                 stream->memlen, stream->stream_id,
                 stream->mem, mem));
    if(mem != stream->mem) {
      /* if we didn't get the same buffer this time, we must move the data to
         the beginning */
      memmove(mem, stream->mem, stream->memlen);
      stream->len = len - stream->memlen;
      stream->mem = mem;
    }
    if(httpc->pause_stream_id == stream->stream_id && !stream->pausedata) {
      /* We have paused nghttp2, but we have no pause data (see
         on_data_chunk_recv). */
      httpc->pause_stream_id = 0;
      if(h2_process_pending_input(data, httpc, &result) != 0) {
        *err = result;
        return -1;
      }
    }
  }
  else if(stream->pausedata) {
    DEBUGASSERT(httpc->pause_stream_id == stream->stream_id);
    nread = MIN(len, stream->pauselen);
    memcpy(mem, stream->pausedata, nread);

    stream->pausedata += nread;
    stream->pauselen -= nread;

    infof(data, "%zu data bytes written\n", nread);
    if(stream->pauselen == 0) {
      DEBUGF(infof(data, "Unpaused by stream %u\n", stream->stream_id));
      DEBUGASSERT(httpc->pause_stream_id == stream->stream_id);
      httpc->pause_stream_id = 0;

      stream->pausedata = NULL;
      stream->pauselen = 0;

      /* When NGHTTP2_ERR_PAUSE is returned from
         data_source_read_callback, we might not process DATA frame
         fully.  Calling nghttp2_session_mem_recv() again will
         continue to process DATA frame, but if there is no incoming
         frames, then we have to call it again with 0-length data.
         Without this, on_stream_close callback will not be called,
         and stream could be hanged. */
      if(h2_process_pending_input(data, httpc, &result) != 0) {
        *err = result;
        return -1;
      }
    }
    DEBUGF(infof(data, "http2_recv: returns unpaused %zd bytes on stream %u\n",
                 nread, stream->stream_id));
    return nread;
  }
  else if(httpc->pause_stream_id) {
    /* If a stream paused nghttp2_session_mem_recv previously, and has
       not processed all data, it still refers to the buffer in
       nghttp2_session.  If we call nghttp2_session_mem_recv(), we may
       overwrite that buffer.  To avoid that situation, just return
       here with CURLE_AGAIN.  This could be busy loop since data in
       socket is not read.  But it seems that usually streams are
       notified with its drain property, and socket is read again
       quickly. */
    DEBUGF(infof(data, "stream %x is paused, pause id: %x\n",
                 stream->stream_id, httpc->pause_stream_id));
    *err = CURLE_AGAIN;
    return -1;
  }
  else {
    char *inbuf;
    /* remember where to store incoming data for this stream and how big the
       buffer is */
    stream->mem = mem;
    stream->len = len;
    stream->memlen = 0;

    if(httpc->inbuflen == 0) {
      nread = ((Curl_recv *)httpc->recv_underlying)(
          conn, FIRSTSOCKET, httpc->inbuf, H2_BUFSIZE, &result);

      if(nread == -1) {
        if(result != CURLE_AGAIN)
          failf(data, "Failed receiving HTTP2 data");
        else if(stream->closed)
          /* received when the stream was already closed! */
          return http2_handle_stream_close(conn, data, stream, err);

        *err = result;
        return -1;
      }

      if(nread == 0) {
        failf(data, "Unexpected EOF");
        *err = CURLE_RECV_ERROR;
        return -1;
      }

      DEBUGF(infof(data, "nread=%zd\n", nread));

      httpc->inbuflen = nread;
      inbuf = httpc->inbuf;
    }
    else {
      nread = httpc->inbuflen - httpc->nread_inbuf;
      inbuf = httpc->inbuf + httpc->nread_inbuf;

      DEBUGF(infof(data, "Use data left in connection buffer, nread=%zd\n",
                   nread));
    }
    rv = nghttp2_session_mem_recv(httpc->h2, (const uint8_t *)inbuf, nread);

    if(nghttp2_is_fatal((int)rv)) {
      failf(data, "nghttp2_session_mem_recv() returned %d:%s\n",
            rv, nghttp2_strerror((int)rv));
      *err = CURLE_RECV_ERROR;
      return 0;
    }
    DEBUGF(infof(data, "nghttp2_session_mem_recv() returns %zd\n", rv));
    if(nread == rv) {
      DEBUGF(infof(data, "All data in connection buffer processed\n"));
      httpc->inbuflen = 0;
      httpc->nread_inbuf = 0;
    }
    else {
      httpc->nread_inbuf += rv;
      DEBUGF(infof(data, "%zu bytes left in connection buffer\n",
                   httpc->inbuflen - httpc->nread_inbuf));
    }
    /* Always send pending frames in nghttp2 session, because
       nghttp2_session_mem_recv() may queue new frame */
    rv = h2_session_send(data, httpc->h2);
    if(rv != 0) {
      *err = CURLE_SEND_ERROR;
      return 0;
    }

    if(should_close_session(httpc)) {
      DEBUGF(infof(data, "http2_recv: nothing to do in this session\n"));
      *err = CURLE_HTTP2;
      return -1;
    }
  }
  if(stream->memlen) {
    ssize_t retlen = stream->memlen;
    DEBUGF(infof(data, "http2_recv: returns %zd for stream %u\n",
                 retlen, stream->stream_id));
    stream->memlen = 0;

    if(httpc->pause_stream_id == stream->stream_id) {
      /* data for this stream is returned now, but this stream caused a pause
         already so we need it called again asap */
      DEBUGF(infof(data, "Data returned for PAUSED stream %u\n",
                   stream->stream_id));
    }
    else if(!stream->closed) {
      DEBUGASSERT(httpc->drain_total >= data->state.drain);
      httpc->drain_total -= data->state.drain;
      data->state.drain = 0; /* this stream is hereby drained */
    }

    return retlen;
  }
  /* If stream is closed, return 0 to signal the http routine to close
     the connection */
  if(stream->closed) {
    return http2_handle_stream_close(conn, data, stream, err);
  }
  *err = CURLE_AGAIN;
  DEBUGF(infof(data, "http2_recv returns AGAIN for stream %u\n",
               stream->stream_id));
  return -1;
}
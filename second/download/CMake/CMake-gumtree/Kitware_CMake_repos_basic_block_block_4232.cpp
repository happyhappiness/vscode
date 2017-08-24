{
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
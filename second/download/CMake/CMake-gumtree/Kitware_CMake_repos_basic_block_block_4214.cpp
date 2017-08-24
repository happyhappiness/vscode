{
  char *trailer_pos, *trailer_end;
  CURLcode result;
  struct http_conn *httpc = &conn->proto.httpc;

  if(httpc->pause_stream_id == stream->stream_id) {
    httpc->pause_stream_id = 0;
  }

  DEBUGASSERT(httpc->drain_total >= data->state.drain);
  httpc->drain_total -= data->state.drain;
  data->state.drain = 0;

  if(httpc->pause_stream_id == 0) {
    if(h2_process_pending_input(data, httpc, err) != 0) {
      return -1;
    }
  }

  DEBUGASSERT(data->state.drain == 0);

  /* Reset to FALSE to prevent infinite loop in readwrite_data function. */
  stream->closed = FALSE;
  if(stream->error_code != NGHTTP2_NO_ERROR) {
    failf(data, "HTTP/2 stream %u was not closed cleanly: %s (err %d)",
          stream->stream_id, Curl_http2_strerror(stream->error_code),
          stream->error_code);
    *err = CURLE_HTTP2_STREAM;
    return -1;
  }

  if(!stream->bodystarted) {
    failf(data, "HTTP/2 stream %u was closed cleanly, but before getting "
          " all response header fields, teated as error",
          stream->stream_id);
    *err = CURLE_HTTP2_STREAM;
    return -1;
  }

  if(stream->trailer_recvbuf && stream->trailer_recvbuf->buffer) {
    trailer_pos = stream->trailer_recvbuf->buffer;
    trailer_end = trailer_pos + stream->trailer_recvbuf->size_used;

    for(; trailer_pos < trailer_end;) {
      uint32_t n;
      memcpy(&n, trailer_pos, sizeof(n));
      trailer_pos += sizeof(n);

      result = Curl_client_write(conn, CLIENTWRITE_HEADER, trailer_pos, n);
      if(result) {
        *err = result;
        return -1;
      }

      trailer_pos += n + 1;
    }
  }

  stream->close_handled = TRUE;

  DEBUGF(infof(data, "http2_recv returns 0, http2_handle_stream_close\n"));
  return 0;
}
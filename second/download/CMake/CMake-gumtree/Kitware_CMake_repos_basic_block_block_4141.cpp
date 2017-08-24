{
  struct connectdata *conn = (struct connectdata *)userp;
  struct http_conn *httpc = &conn->proto.httpc;
  struct Curl_easy *data_s = NULL;
  struct HTTP *stream = NULL;
  static int lastStream = -1;
  int rv;
  size_t left, ncopy;
  int32_t stream_id = frame->hd.stream_id;

  if(!stream_id) {
    /* stream ID zero is for connection-oriented stuff */
    if(frame->hd.type == NGHTTP2_SETTINGS) {
      uint32_t max_conn = httpc->settings.max_concurrent_streams;
      DEBUGF(infof(conn->data, "Got SETTINGS\n"));
      httpc->settings.max_concurrent_streams =
        nghttp2_session_get_remote_settings(
          session, NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS);
      httpc->settings.enable_push =
        nghttp2_session_get_remote_settings(
          session, NGHTTP2_SETTINGS_ENABLE_PUSH);
      DEBUGF(infof(conn->data, "MAX_CONCURRENT_STREAMS == %d\n",
                   httpc->settings.max_concurrent_streams));
      DEBUGF(infof(conn->data, "ENABLE_PUSH == %s\n",
                   httpc->settings.enable_push?"TRUE":"false"));
      if(max_conn != httpc->settings.max_concurrent_streams) {
        /* only signal change if the value actually changed */
        infof(conn->data,
              "Connection state changed (MAX_CONCURRENT_STREAMS updated)!\n");
        Curl_multi_connchanged(conn->data->multi);
      }
    }
    return 0;
  }
  data_s = nghttp2_session_get_stream_user_data(session, stream_id);
  if(lastStream != stream_id) {
    lastStream = stream_id;
  }
  if(!data_s) {
    DEBUGF(infof(conn->data,
                 "No Curl_easy associated with stream: %x\n",
                 stream_id));
    return 0;
  }

  stream = data_s->req.protop;
  if(!stream) {
    DEBUGF(infof(conn->data, "No proto pointer for stream: %x\n",
                 stream_id));
    return NGHTTP2_ERR_CALLBACK_FAILURE;
  }

  DEBUGF(infof(data_s, "on_frame_recv() header %x stream %x\n",
               frame->hd.type, stream_id));

  switch(frame->hd.type) {
  case NGHTTP2_DATA:
    /* If body started on this stream, then receiving DATA is illegal. */
    if(!stream->bodystarted) {
      rv = nghttp2_submit_rst_stream(session, NGHTTP2_FLAG_NONE,
                                     stream_id, NGHTTP2_PROTOCOL_ERROR);

      if(nghttp2_is_fatal(rv)) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
      }
    }
    break;
  case NGHTTP2_HEADERS:
    if(stream->bodystarted) {
      /* Only valid HEADERS after body started is trailer HEADERS.  We
         buffer them in on_header callback. */
      break;
    }

    /* nghttp2 guarantees that :status is received, and we store it to
       stream->status_code */
    DEBUGASSERT(stream->status_code != -1);

    /* Only final status code signals the end of header */
    if(stream->status_code / 100 != 1) {
      stream->bodystarted = TRUE;
      stream->status_code = -1;
    }

    Curl_add_buffer(stream->header_recvbuf, "\r\n", 2);

    left = stream->header_recvbuf->size_used - stream->nread_header_recvbuf;
    ncopy = MIN(stream->len, left);

    memcpy(&stream->mem[stream->memlen],
           stream->header_recvbuf->buffer + stream->nread_header_recvbuf,
           ncopy);
    stream->nread_header_recvbuf += ncopy;

    DEBUGF(infof(data_s, "Store %zu bytes headers from stream %u at %p\n",
                 ncopy, stream_id, stream->mem));

    stream->len -= ncopy;
    stream->memlen += ncopy;

    data_s->state.drain++;
    httpc->drain_total++;
    {
      /* get the pointer from userp again since it was re-assigned above */
      struct connectdata *conn_s = (struct connectdata *)userp;

      /* if we receive data for another handle, wake that up */
      if(conn_s->data != data_s)
        Curl_expire(data_s, 0, EXPIRE_RUN_NOW);
    }
    break;
  case NGHTTP2_PUSH_PROMISE:
    rv = push_promise(data_s, conn, &frame->push_promise);
    if(rv) { /* deny! */
      rv = nghttp2_submit_rst_stream(session, NGHTTP2_FLAG_NONE,
                                     frame->push_promise.promised_stream_id,
                                     NGHTTP2_CANCEL);
      if(nghttp2_is_fatal(rv)) {
        return rv;
      }
    }
    break;
  default:
    DEBUGF(infof(conn->data, "Got frame type %x for stream %u!\n",
                 frame->hd.type, stream_id));
    break;
  }
  return 0;
}
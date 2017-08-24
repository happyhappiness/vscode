{
  struct HTTP *stream;
  struct Curl_easy *data_s = NULL;
  (void)userp;

  data_s = nghttp2_session_get_stream_user_data(session, frame->hd.stream_id);
  if(!data_s) {
    return 0;
  }

  DEBUGF(infof(data_s, "on_begin_headers() was called\n"));

  if(frame->hd.type != NGHTTP2_HEADERS) {
    return 0;
  }

  stream = data_s->req.protop;
  if(!stream || !stream->bodystarted) {
    return 0;
  }

  /* This is trailer HEADERS started.  Allocate buffer for them. */
  DEBUGF(infof(data_s, "trailer field started\n"));

  DEBUGASSERT(stream->trailer_recvbuf == NULL);

  stream->trailer_recvbuf = Curl_add_buffer_init();
  if(!stream->trailer_recvbuf) {
    return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
  }

  return 0;
}
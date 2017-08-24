{
  struct Curl_easy *data_s;
  struct HTTP *stream = NULL;
  size_t nread;
  (void)source;
  (void)userp;

  if(stream_id) {
    /* get the stream from the hash based on Stream ID, stream ID zero is for
       connection-oriented stuff */
    data_s = nghttp2_session_get_stream_user_data(session, stream_id);
    if(!data_s)
      /* Receiving a Stream ID not in the hash should not happen, this is an
         internal error more than anything else! */
      return NGHTTP2_ERR_CALLBACK_FAILURE;

    stream = data_s->req.protop;
    if(!stream)
      return NGHTTP2_ERR_CALLBACK_FAILURE;
  }
  else
    return NGHTTP2_ERR_INVALID_ARGUMENT;

  nread = MIN(stream->upload_len, length);
  if(nread > 0) {
    memcpy(buf, stream->upload_mem, nread);
    stream->upload_mem += nread;
    stream->upload_len -= nread;
    if(data_s->state.infilesize != -1)
      stream->upload_left -= nread;
  }

  if(stream->upload_left == 0)
    *data_flags = NGHTTP2_DATA_FLAG_EOF;
  else if(nread == 0)
    return NGHTTP2_ERR_DEFERRED;

  DEBUGF(infof(data_s, "data_source_read_callback: "
               "returns %zu bytes stream %u\n",
               nread, stream_id));

  return nread;
}
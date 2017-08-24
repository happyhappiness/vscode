{
  struct HTTP *stream;
  struct Curl_easy *data_s;
  size_t nread;
  struct connectdata *conn = (struct connectdata *)userp;
  (void)session;
  (void)flags;
  (void)data;

  DEBUGASSERT(stream_id); /* should never be a zero stream ID here */

  /* get the stream from the hash based on Stream ID */
  data_s = nghttp2_session_get_stream_user_data(session, stream_id);
  if(!data_s)
    /* Receiving a Stream ID not in the hash should not happen, this is an
       internal error more than anything else! */
    return NGHTTP2_ERR_CALLBACK_FAILURE;

  stream = data_s->req.protop;
  if(!stream)
    return NGHTTP2_ERR_CALLBACK_FAILURE;

  nread = MIN(stream->len, len);
  memcpy(&stream->mem[stream->memlen], data, nread);

  stream->len -= nread;
  stream->memlen += nread;

  data_s->state.drain++;
  conn->proto.httpc.drain_total++;

  /* if we receive data for another handle, wake that up */
  if(conn->data != data_s)
    Curl_expire(data_s, 0, EXPIRE_RUN_NOW);

  DEBUGF(infof(data_s, "%zu data received for stream %u "
               "(%zu left in buffer %p, total %zu)\n",
               nread, stream_id,
               stream->len, stream->mem,
               stream->memlen));

  if(nread < len) {
    stream->pausedata = data + nread;
    stream->pauselen = len - nread;
    DEBUGF(infof(data_s, "NGHTTP2_ERR_PAUSE - %zu bytes out of buffer"
                 ", stream %u\n",
                 len - nread, stream_id));
    data_s->easy_conn->proto.httpc.pause_stream_id = stream_id;

    return NGHTTP2_ERR_PAUSE;
  }

  /* pause execution of nghttp2 if we received data for another handle
     in order to process them first. */
  if(conn->data != data_s) {
    data_s->easy_conn->proto.httpc.pause_stream_id = stream_id;

    return NGHTTP2_ERR_PAUSE;
  }

  return 0;
}
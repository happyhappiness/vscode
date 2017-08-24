{
    /* get the stream from the hash based on Stream ID, stream ID zero is for
       connection-oriented stuff */
    data_s = nghttp2_session_get_stream_user_data(session, stream_id);
    if(!data_s) {
      /* We could get stream ID not in the hash.  For example, if we
         decided to reject stream (e.g., PUSH_PROMISE). */
      return 0;
    }
    DEBUGF(infof(data_s, "on_stream_close(), %s (err %d), stream %u\n",
                 Curl_http2_strerror(error_code), error_code, stream_id));
    stream = data_s->req.protop;
    if(!stream)
      return NGHTTP2_ERR_CALLBACK_FAILURE;

    stream->error_code = error_code;
    stream->closed = TRUE;
    data_s->state.drain++;
    conn->proto.httpc.drain_total++;

    /* remove the entry from the hash as the stream is now gone */
    nghttp2_session_set_stream_user_data(session, stream_id, 0);
    DEBUGF(infof(data_s, "Removed stream %u hash!\n", stream_id));
  }
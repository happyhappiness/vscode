{
    struct HTTP *stream;
    struct HTTP *newstream;
    struct curl_pushheaders heads;
    CURLMcode rc;
    struct http_conn *httpc;
    size_t i;
    /* clone the parent */
    struct Curl_easy *newhandle = duphandle(data);
    if(!newhandle) {
      infof(data, "failed to duplicate handle\n");
      rv = 1; /* FAIL HARD */
      goto fail;
    }

    heads.data = data;
    heads.frame = frame;
    /* ask the application */
    DEBUGF(infof(data, "Got PUSH_PROMISE, ask application!\n"));

    stream = data->req.protop;
    if(!stream) {
      failf(data, "Internal NULL stream!\n");
      (void)Curl_close(newhandle);
      rv = 1;
      goto fail;
    }

    rv = data->multi->push_cb(data, newhandle,
                              stream->push_headers_used, &heads,
                              data->multi->push_userp);

    /* free the headers again */
    for(i=0; i<stream->push_headers_used; i++)
      free(stream->push_headers[i]);
    free(stream->push_headers);
    stream->push_headers = NULL;
    stream->push_headers_used = 0;

    if(rv) {
      /* denied, kill off the new handle again */
      http2_stream_free(newhandle->req.protop);
      (void)Curl_close(newhandle);
      goto fail;
    }

    newstream = newhandle->req.protop;
    newstream->stream_id = frame->promised_stream_id;
    newhandle->req.maxdownload = -1;
    newhandle->req.size = -1;

    /* approved, add to the multi handle and immediately switch to PERFORM
       state with the given connection !*/
    rc = Curl_multi_add_perform(data->multi, newhandle, conn);
    if(rc) {
      infof(data, "failed to add handle to multi\n");
      http2_stream_free(newhandle->req.protop);
      Curl_close(newhandle);
      rv = 1;
      goto fail;
    }

    httpc = &conn->proto.httpc;
    nghttp2_session_set_stream_user_data(httpc->h2,
                                         frame->promised_stream_id, newhandle);
  }
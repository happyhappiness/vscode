{
    /* send new weight and/or dependency */
    nghttp2_priority_spec pri_spec;
    int rv;

    h2_pri_spec(data, &pri_spec);

    DEBUGF(infof(data, "Queuing PRIORITY on stream %u (easy %p)\n",
                 stream->stream_id, data));
    rv = nghttp2_submit_priority(h2, NGHTTP2_FLAG_NONE, stream->stream_id,
                                 &pri_spec);
    if(rv)
      return rv;
  }
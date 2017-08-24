f(stream->memlen) {
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
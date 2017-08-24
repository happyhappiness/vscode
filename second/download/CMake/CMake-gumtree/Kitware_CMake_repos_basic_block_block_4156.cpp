{
    stream->pausedata = data + nread;
    stream->pauselen = len - nread;
    DEBUGF(infof(data_s, "NGHTTP2_ERR_PAUSE - %zu bytes out of buffer"
                 ", stream %u\n",
                 len - nread, stream_id));
    data_s->easy_conn->proto.httpc.pause_stream_id = stream_id;

    return NGHTTP2_ERR_PAUSE;
  }
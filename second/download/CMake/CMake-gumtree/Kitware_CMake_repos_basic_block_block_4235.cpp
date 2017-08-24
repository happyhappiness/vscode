{
    DEBUGASSERT(httpc->pause_stream_id == stream->stream_id);
    nread = MIN(len, stream->pauselen);
    memcpy(mem, stream->pausedata, nread);

    stream->pausedata += nread;
    stream->pauselen -= nread;

    infof(data, "%zu data bytes written\n", nread);
    if(stream->pauselen == 0) {
      DEBUGF(infof(data, "Unpaused by stream %u\n", stream->stream_id));
      DEBUGASSERT(httpc->pause_stream_id == stream->stream_id);
      httpc->pause_stream_id = 0;

      stream->pausedata = NULL;
      stream->pauselen = 0;

      /* When NGHTTP2_ERR_PAUSE is returned from
         data_source_read_callback, we might not process DATA frame
         fully.  Calling nghttp2_session_mem_recv() again will
         continue to process DATA frame, but if there is no incoming
         frames, then we have to call it again with 0-length data.
         Without this, on_stream_close callback will not be called,
         and stream could be hanged. */
      if(h2_process_pending_input(data, httpc, &result) != 0) {
        *err = result;
        return -1;
      }
    }
    DEBUGF(infof(data, "http2_recv: returns unpaused %zd bytes on stream %u\n",
                 nread, stream->stream_id));
    return nread;
  }
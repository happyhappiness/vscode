f(httpc->pause_stream_id == stream->stream_id && !stream->pausedata) {
      /* We have paused nghttp2, but we have no pause data (see
         on_data_chunk_recv). */
      httpc->pause_stream_id = 0;
      if(h2_process_pending_input(data, httpc, &result) != 0) {
        *err = result;
        return -1;
      }
    }
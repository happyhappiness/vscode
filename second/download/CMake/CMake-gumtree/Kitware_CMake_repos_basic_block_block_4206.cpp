{
    failf(data,
          "h2_process_pending_input: nghttp2_session_mem_recv() returned "
          "%d:%s\n", rv, nghttp2_strerror((int)rv));
    *err = CURLE_RECV_ERROR;
    return -1;
  }
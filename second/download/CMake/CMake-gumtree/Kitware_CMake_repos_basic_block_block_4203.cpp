{
    DEBUGF(infof(data,
                 "h2_process_pending_input: nothing to do in this session\n"));
    *err = CURLE_HTTP2;
    return -1;
  }
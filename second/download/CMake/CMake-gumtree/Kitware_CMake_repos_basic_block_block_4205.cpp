{
    httpc->nread_inbuf += rv;
    DEBUGF(infof(data,
                 "h2_process_pending_input: %zu bytes left in connection "
                 "buffer\n",
                 httpc->inbuflen - httpc->nread_inbuf));
  }
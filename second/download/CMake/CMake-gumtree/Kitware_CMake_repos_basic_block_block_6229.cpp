f((*in_connect)->send_pipe.size || (*in_connect)->recv_pipe.size)
      /* pipelining */
      *protocol_done = TRUE;
    else if(!*asyncp) {
      /* DNS resolution is done: that's either because this is a reused
         connection, in which case DNS was unnecessary, or because DNS
         really did finish already (synch resolver/fast async resolve) */
      result = Curl_setup_conn(*in_connect, protocol_done);
    }
CURLcode Curl_connect(struct SessionHandle *data,
                      struct connectdata **in_connect,
                      bool *asyncp,
                      bool *protocol_done)
{
  CURLcode code;

  *asyncp = FALSE; /* assume synchronous resolves by default */

  /* call the stuff that needs to be called */
  code = create_conn(data, in_connect, asyncp);

  if(CURLE_OK == code) {
    /* no error */
    if((*in_connect)->send_pipe->size || (*in_connect)->recv_pipe->size)
      /* pipelining */
      *protocol_done = TRUE;
    else if(!*asyncp) {
      /* DNS resolution is done: that's either because this is a reused
         connection, in which case DNS was unnecessary, or because DNS
         really did finish already (synch resolver/fast async resolve) */
      code = Curl_setup_conn(*in_connect, protocol_done);
    }
  }

  if(code == CURLE_NO_CONNECTION_AVAILABLE) {
    *in_connect = NULL;
    return code;
  }

  if(code && *in_connect) {
    /* We're not allowed to return failure with memory left allocated
       in the connectdata struct, free those here */
    Curl_disconnect(*in_connect, FALSE); /* close the connection */
    *in_connect = NULL;           /* return a NULL */
  }

  return code;
}
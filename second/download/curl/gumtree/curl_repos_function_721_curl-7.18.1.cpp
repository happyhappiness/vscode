CURLcode Curl_connect(struct SessionHandle *data,
                      struct connectdata **in_connect,
                      bool *asyncp,
                      bool *protocol_done)
{
  CURLcode code;
  struct Curl_dns_entry *dns;

  *asyncp = FALSE; /* assume synchronous resolves by default */

  /* call the stuff that needs to be called */
  code = CreateConnection(data, in_connect, &dns, asyncp);

  if(CURLE_OK == code) {
    /* no error */
    if((*in_connect)->send_pipe->size +
       (*in_connect)->recv_pipe->size != 0)
      /* pipelining */
      *protocol_done = TRUE;
    else {
      if(dns || !*asyncp)
        /* If an address is available it means that we already have the name
           resolved, OR it isn't async. if this is a re-used connection 'dns'
           will be NULL here. Continue connecting from here */
        code = SetupConnection(*in_connect, dns, protocol_done);
      /* else
         response will be received and treated async wise */
    }
  }

  if(CURLE_OK != code && *in_connect) {
    /* We're not allowed to return failure with memory left allocated
       in the connectdata struct, free those here */
    Curl_disconnect(*in_connect); /* close the connection */
    *in_connect = NULL;           /* return a NULL */
  }

  return code;
}
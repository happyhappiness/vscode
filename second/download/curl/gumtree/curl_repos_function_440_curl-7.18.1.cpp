static CURLcode
connect_host(struct SessionHandle *data,
             struct connectdata **conn)
{
  CURLcode res = CURLE_OK;

  bool async;
  bool protocol_done=TRUE; /* will be TRUE always since this is only used
                                within the easy interface */
  Curl_pgrsTime(data, TIMER_STARTSINGLE);
  res = Curl_connect(data, conn, &async, &protocol_done);

  if((CURLE_OK == res) && async) {
    /* Now, if async is TRUE here, we need to wait for the name
       to resolve */
    res = Curl_wait_for_resolv(*conn, NULL);
    if(CURLE_OK == res)
      /* Resolved, continue with the connection */
      res = Curl_async_resolved(*conn, &protocol_done);
    else
      /* if we can't resolve, we kill this "connection" now */
      (void)Curl_disconnect(*conn);
  }

  return res;
}
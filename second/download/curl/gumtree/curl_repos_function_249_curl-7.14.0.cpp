static CURLcode
Curl_connect_host(struct SessionHandle *data,
                  struct connectdata **conn)
{
  CURLcode res = CURLE_OK;
  int urlchanged = FALSE;

  do {
    bool async;
    bool protocol_done=TRUE; /* will be TRUE always since this is only used
                                within the easy interface */
    Curl_pgrsTime(data, TIMER_STARTSINGLE);
    data->change.url_changed = FALSE;
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
    if(res)
      break;

    /* If a callback (or something) has altered the URL we should use within
       the Curl_connect(), we detect it here and act as if we are redirected
       to the new URL */
    urlchanged = data->change.url_changed;
    if ((CURLE_OK == res) && urlchanged) {
      res = Curl_done(conn, res);
      if(CURLE_OK == res) {
        char *gotourl = strdup(data->change.url);
        res = Curl_follow(data, gotourl, FALSE);
        if(res)
          free(gotourl);
      }
    }
  } while (urlchanged && res == CURLE_OK);

  return res;
}
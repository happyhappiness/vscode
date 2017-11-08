CURLcode Curl_resolver_wait_resolv(struct connectdata *conn,
                                   struct Curl_dns_entry **entry)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  long timeout;
  struct curltime now = Curl_tvnow();
  struct Curl_dns_entry *temp_entry;

  if(entry)
    *entry = NULL; /* clear on entry */

  timeout = Curl_timeleft(data, &now, TRUE);
  if(timeout < 0) {
    /* already expired! */
    connclose(conn, "Timed out before name resolve started");
    return CURLE_OPERATION_TIMEDOUT;
  }
  if(!timeout)
    timeout = CURL_TIMEOUT_RESOLVE * 1000; /* default name resolve timeout */

  /* Wait for the name resolve query to complete. */
  while(!result) {
    struct timeval *tvp, tv, store;
    int itimeout;
    int timeout_ms;

    itimeout = (timeout > (long)INT_MAX) ? INT_MAX : (int)timeout;

    store.tv_sec = itimeout/1000;
    store.tv_usec = (itimeout%1000)*1000;

    tvp = ares_timeout((ares_channel)data->state.resolver, &store, &tv);

    /* use the timeout period ares returned to us above if less than one
       second is left, otherwise just use 1000ms to make sure the progress
       callback gets called frequent enough */
    if(!tvp->tv_sec)
      timeout_ms = (int)(tvp->tv_usec/1000);
    else
      timeout_ms = 1000;

    waitperform(conn, timeout_ms);
    result = Curl_resolver_is_resolved(conn, &temp_entry);

    if(result || conn->async.done)
      break;

    if(Curl_pgrsUpdate(conn))
      result = CURLE_ABORTED_BY_CALLBACK;
    else {
      struct curltime now2 = Curl_tvnow();
      time_t timediff = Curl_tvdiff(now2, now); /* spent time */
      if(timediff <= 0)
        timeout -= 1; /* always deduct at least 1 */
      else if(timediff > timeout)
        timeout = -1;
      else
        timeout -= (long)timediff;
      now = now2; /* for next loop */
    }
    if(timeout < 0)
      result = CURLE_OPERATION_TIMEDOUT;
  }
  if(result)
    /* failure, so we cancel the ares operation */
    ares_cancel((ares_channel)data->state.resolver);

  /* Operation complete, if the lookup was successful we now have the entry
     in the cache. */
  if(entry)
    *entry = conn->async.dns;

  if(result)
    /* close the connection, since we can't return failure here without
       cleaning up this connection properly.
       TODO: remove this action from here, it is not a name resolver decision.
    */
    connclose(conn, "c-ares resolve failed");

  return result;
}
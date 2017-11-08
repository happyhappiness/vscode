CURLcode Curl_resolver_wait_resolv(struct connectdata *conn,
                                   struct Curl_dns_entry **entry)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  long timeout;
  struct timeval now = Curl_tvnow();
  struct Curl_dns_entry *temp_entry;

  timeout = Curl_timeleft(data, &now, TRUE);
  if(!timeout)
    timeout = CURL_TIMEOUT_RESOLVE * 1000; /* default name resolve timeout */

  /* Wait for the name resolve query to complete. */
  for(;;) {
    struct timeval *tvp, tv, store;
    long timediff;
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
    Curl_resolver_is_resolved(conn,&temp_entry);

    if(conn->async.done)
      break;

    if(Curl_pgrsUpdate(conn)) {
      result = CURLE_ABORTED_BY_CALLBACK;
      timeout = -1; /* trigger the cancel below */
    }
    else {
      struct timeval now2 = Curl_tvnow();
      timediff = Curl_tvdiff(now2, now); /* spent time */
      timeout -= timediff?timediff:1; /* always deduct at least 1 */
      now = now2; /* for next loop */
    }

    if(timeout < 0) {
      /* our timeout, so we cancel the ares operation */
      ares_cancel((ares_channel)data->state.resolver);
      break;
    }
  }

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
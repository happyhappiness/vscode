CURLcode Curl_wait_for_resolv(struct connectdata *conn,
                              struct Curl_dns_entry **entry)
{
  CURLcode rc=CURLE_OK;
  struct SessionHandle *data = conn->data;
  long timeout;

  /* now, see if there's a connect timeout or a regular timeout to
     use instead of the default one */
  if(conn->data->set.connecttimeout)
    timeout = conn->data->set.connecttimeout;
  else if(conn->data->set.timeout)
    timeout = conn->data->set.timeout;
  else
    timeout = CURL_TIMEOUT_RESOLVE * 1000; /* default name resolve timeout */

  /* Wait for the name resolve query to complete. */
  while(1) {
    struct timeval *tvp, tv, store;
    struct timeval now = Curl_tvnow();
    long timediff;

    store.tv_sec = (int)timeout/1000;
    store.tv_usec = (timeout%1000)*1000;

    tvp = ares_timeout(data->state.areschannel, &store, &tv);

    /* use the timeout period ares returned to us above */
    ares_waitperform(conn, (int)(tvp->tv_sec * 1000 + tvp->tv_usec/1000));

    if(conn->async.done)
      break;

    timediff = Curl_tvdiff(Curl_tvnow(), now); /* spent time */
    timeout -= timediff?timediff:1; /* always deduct at least 1 */
    if(timeout < 0) {
      /* our timeout, so we cancel the ares operation */
      ares_cancel(data->state.areschannel);
      break;
    }
  }

  /* Operation complete, if the lookup was successful we now have the entry
     in the cache. */

  if(entry)
    *entry = conn->async.dns;

  if(!conn->async.dns) {
    /* a name was not resolved */
    if((timeout < 0) || (conn->async.status == ARES_ETIMEOUT)) {
      failf(data, "Resolving host timed out: %s", conn->host.dispname);
      rc = CURLE_COULDNT_RESOLVE_HOST;
    }
    else if(conn->async.done) {
      failf(data, "Could not resolve host: %s (%s)", conn->host.dispname,
            ares_strerror(conn->async.status));
      rc = CURLE_COULDNT_RESOLVE_HOST;
    }
    else
      rc = CURLE_OPERATION_TIMEDOUT;

    /* close the connection, since we can't return failure here without
       cleaning up this connection properly */
    conn->bits.close = TRUE;
  }

  return rc;
}
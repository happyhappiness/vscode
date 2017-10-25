CURLcode Curl_wait_for_resolv(struct connectdata *conn,
                              struct Curl_dns_entry **entry)
{
  CURLcode rc=CURLE_OK;
  struct SessionHandle *data = conn->data;
  long timeout = CURL_TIMEOUT_RESOLVE; /* default name resolve timeout */

  /* now, see if there's a connect timeout or a regular timeout to
     use instead of the default one */
  if(conn->data->set.connecttimeout)
    timeout = conn->data->set.connecttimeout;
  else if(conn->data->set.timeout)
    timeout = conn->data->set.timeout;

  /* We convert the number of seconds into number of milliseconds here: */
  if(timeout < 2147483)
    /* maximum amount of seconds that can be multiplied with 1000 and
       still fit within 31 bits */
    timeout *= 1000;
  else
    timeout = 0x7fffffff; /* ridiculous amount of time anyway */

  /* Wait for the name resolve query to complete. */
  while (1) {
    int nfds=0;
    fd_set read_fds, write_fds;
    struct timeval *tvp, tv, store;
    int count;
    struct timeval now = Curl_tvnow();
    long timediff;

    store.tv_sec = (int)timeout/1000;
    store.tv_usec = (timeout%1000)*1000;

    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    nfds = ares_fds(data->state.areschannel, &read_fds, &write_fds);
    if (nfds == 0)
      /* no file descriptors means we're done waiting */
      break;
    tvp = ares_timeout(data->state.areschannel, &store, &tv);
    count = select(nfds, &read_fds, &write_fds, NULL, tvp);
    if (count < 0 && errno != EINVAL)
      break;

    ares_process(data->state.areschannel, &read_fds, &write_fds);

    timediff = Curl_tvdiff(Curl_tvnow(), now); /* spent time */
    timeout -= timediff?timediff:1; /* always deduct at least 1 */
    if (timeout < 0) {
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
      rc = CURLE_OPERATION_TIMEDOUT;
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
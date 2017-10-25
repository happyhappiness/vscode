int Curl_resolv(struct connectdata *conn,
                char *hostname,
                int port,
                struct Curl_dns_entry **entry)
{
  char *entry_id = NULL;
  struct Curl_dns_entry *dns = NULL;
  size_t entry_len;
  int wait;
  struct SessionHandle *data = conn->data;
  CURLcode result;
  int rc;
  *entry = NULL;

#ifdef HAVE_SIGSETJMP
  /* this allows us to time-out from the name resolver, as the timeout
     will generate a signal and we will siglongjmp() from that here */
  if(!data->set.no_signal && sigsetjmp(curl_jmpenv, 1)) {
    /* this is coming from a siglongjmp() */
    failf(data, "name lookup timed out");
    return CURLRESOLV_ERROR;
  }
#endif

  /* Create an entry id, based upon the hostname and port */
  entry_id = create_hostcache_id(hostname, port);
  /* If we can't create the entry id, fail */
  if (!entry_id)
    return CURLRESOLV_ERROR;

  entry_len = strlen(entry_id);

  if(data->share)
    Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

  /* See if its already in our dns cache */
  dns = Curl_hash_pick(data->hostcache, entry_id, entry_len+1);

  if(data->share)
    Curl_share_unlock(data, CURL_LOCK_DATA_DNS);

  /* free the allocated entry_id again */
  free(entry_id);

  rc = CURLRESOLV_ERROR; /* default to failure */

  if (!dns) {
    /* The entry was not in the cache. Resolve it to IP address */

    Curl_addrinfo *addr;

    /* Check what IP specifics the app has requested and if we can provide it.
     * If not, bail out. */
    if(!Curl_ipvalid(data))
      return CURLRESOLV_ERROR;

    /* If Curl_getaddrinfo() returns NULL, 'wait' might be set to a non-zero
       value indicating that we need to wait for the response to the resolve
       call */
    addr = Curl_getaddrinfo(conn, hostname, port, &wait);

    if (!addr) {
      if(wait) {
        /* the response to our resolve call will come asynchronously at
           a later time, good or bad */
        /* First, check that we haven't received the info by now */
        result = Curl_is_resolved(conn, &dns);
        if(result) /* error detected */
          return CURLRESOLV_ERROR;
        if(dns)
          rc = CURLRESOLV_RESOLVED; /* pointer provided */
        else
          rc = CURLRESOLV_PENDING; /* no info yet */
      }
    }
    else {
      if(data->share)
        Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

      /* we got a response, store it in the cache */
      dns = Curl_cache_addr(data, addr, hostname, port);

      if(data->share)
        Curl_share_unlock(data, CURL_LOCK_DATA_DNS);

      if(!dns)
        /* returned failure, bail out nicely */
        Curl_freeaddrinfo(addr);
      else
        rc = CURLRESOLV_RESOLVED;
    }
  }
  else {
    if(data->share)
      Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);
    dns->inuse++; /* we use it! */
    if(data->share)
      Curl_share_unlock(data, CURL_LOCK_DATA_DNS);
    rc = CURLRESOLV_RESOLVED;
  }

  *entry = dns;

  return rc;
}
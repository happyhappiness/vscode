int Curl_resolv(struct connectdata *conn,
                const char *hostname,
                int port,
                struct Curl_dns_entry **entry)
{
  char *entry_id = NULL;
  struct Curl_dns_entry *dns = NULL;
  size_t entry_len;
  struct SessionHandle *data = conn->data;
  CURLcode result;
  int rc = CURLRESOLV_ERROR; /* default to failure */

  *entry = NULL;

  /* Create an entry id, based upon the hostname and port */
  entry_id = create_hostcache_id(hostname, port);
  /* If we can't create the entry id, fail */
  if(!entry_id)
    return rc;

  entry_len = strlen(entry_id);

  if(data->share)
    Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

  /* See if its already in our dns cache */
  dns = Curl_hash_pick(data->dns.hostcache, entry_id, entry_len+1);

  /* free the allocated entry_id again */
  free(entry_id);

  infof(data, "Hostname was %sfound in DNS cache\n", dns?"":"NOT ");

  /* See whether the returned entry is stale. Done before we release lock */
  if(remove_entry_if_stale(data, dns)) {
    infof(data, "Hostname in DNS cache was stale, zapped\n");
    dns = NULL; /* the memory deallocation is being handled by the hash */
  }

  if(dns) {
    dns->inuse++; /* we use it! */
    rc = CURLRESOLV_RESOLVED;
  }

  if(data->share)
    Curl_share_unlock(data, CURL_LOCK_DATA_DNS);

  if(!dns) {
    /* The entry was not in the cache. Resolve it to IP address */

    Curl_addrinfo *addr;
    int respwait;

    /* Check what IP specifics the app has requested and if we can provide it.
     * If not, bail out. */
    if(!Curl_ipvalid(conn))
      return CURLRESOLV_ERROR;

    /* If Curl_getaddrinfo() returns NULL, 'respwait' might be set to a
       non-zero value indicating that we need to wait for the response to the
       resolve call */
    addr = Curl_getaddrinfo(conn,
#ifdef DEBUGBUILD
                            (data->set.str[STRING_DEVICE]
                             && !strcmp(data->set.str[STRING_DEVICE],
                                        "LocalHost"))?"localhost":
#endif
                            hostname, port, &respwait);

    if(!addr) {
      if(respwait) {
        /* the response to our resolve call will come asynchronously at
           a later time, good or bad */
        /* First, check that we haven't received the info by now */
        result = Curl_resolver_is_resolved(conn, &dns);
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

  *entry = dns;

  return rc;
}
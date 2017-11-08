static CURLcode addrinfo_callback(void *arg, /* "struct connectdata *" */
                                  int status,
                                  void *addr)
{
  struct connectdata *conn = (struct connectdata *)arg;
  struct Curl_dns_entry *dns = NULL;
  CURLcode rc = CURLE_OK;

  conn->async.status = status;

  if(CURL_ASYNC_SUCCESS == status) {

    /*
     * IPv4: Curl_addrinfo_copy() copies the address and returns an allocated
     * version.
     *
     * IPv6: Curl_addrinfo_copy() returns the input pointer!
     */
    Curl_addrinfo *ai = Curl_addrinfo_copy(addr, conn->async.port);
    if(ai) {
      struct SessionHandle *data = conn->data;

      if(data->share)
        Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

      dns = Curl_cache_addr(data, ai,
                            conn->async.hostname,
                            conn->async.port);
      if(!dns) {
        /* failed to store, cleanup and return error */
        Curl_freeaddrinfo(ai);
        rc = CURLE_OUT_OF_MEMORY;
      }

      if(data->share)
        Curl_share_unlock(data, CURL_LOCK_DATA_DNS);
    }
    else
      rc = CURLE_OUT_OF_MEMORY;
  }

  conn->async.dns = dns;

 /* Set async.done TRUE last in this function since it may be used multi-
    threaded and once this is TRUE the other thread may read fields from the
    async struct */
  conn->async.done = TRUE;

  /* ipv4: The input hostent struct will be freed by ares when we return from
     this function */
  return rc;
}
CURLcode curl_easy_perform(CURL *curl)
{
  struct SessionHandle *data = (struct SessionHandle *)curl;

  if(!data)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  if( ! (data->share && data->share->hostcache) ) {
    /* this handle is not using a shared dns cache */

    if(data->set.global_dns_cache &&
       (data->dns.hostcachetype != HCACHE_GLOBAL)) {
      /* global dns cache was requested but still isn't */
      struct curl_hash *ptr;

      if(data->dns.hostcachetype == HCACHE_PRIVATE)
        /* if the current cache is private, kill it first */
        Curl_hash_destroy(data->dns.hostcache);

      ptr = Curl_global_host_cache_init();
      if(ptr) {
        /* only do this if the global cache init works */
        data->dns.hostcache = ptr;
        data->dns.hostcachetype = HCACHE_GLOBAL;
      }
    }

    if(!data->dns.hostcache) {
      data->dns.hostcachetype = HCACHE_PRIVATE;
      data->dns.hostcache = Curl_mk_dnscache();

      if(!data->dns.hostcache)
        /* While we possibly could survive and do good without a host cache,
           the fact that creating it failed indicates that things are truly
           screwed up and we should bail out! */
        return CURLE_OUT_OF_MEMORY;
    }

  }

  if(!data->state.connc) {
    /* oops, no connection cache, make one up */
    data->state.connc = Curl_mk_connc(CONNCACHE_PRIVATE, -1);
    if(!data->state.connc)
      return CURLE_OUT_OF_MEMORY;
  }

  return Curl_perform(data);
}
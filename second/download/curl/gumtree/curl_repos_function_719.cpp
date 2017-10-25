CURLcode curl_easy_perform(CURL *curl)
{
  struct SessionHandle *data = (struct SessionHandle *)curl;

  if(!data)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  if ( ! (data->share && data->share->hostcache) ) {

    if (Curl_global_host_cache_use(data) &&
        data->hostcache != Curl_global_host_cache_get()) {
      if (data->hostcache)
        Curl_hash_destroy(data->hostcache);
      data->hostcache = Curl_global_host_cache_get();
    }

    if (!data->hostcache) {
      data->hostcache = Curl_mk_dnscache();

      if(!data->hostcache)
        /* While we possibly could survive and do good without a host cache,
           the fact that creating it failed indicates that things are truly
           screwed up and we should bail out! */
        return CURLE_OUT_OF_MEMORY;
    }

  }

  return Curl_perform(data);
}
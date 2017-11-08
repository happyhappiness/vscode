void Curl_global_host_cache_dtor(void)
{
  if(host_cache_initialized) {
    /* first make sure that any custom "CURLOPT_RESOLVE" names are
       cleared off */
    Curl_hostcache_clean(NULL, &hostname_cache);
    /* then free the remaining hash completely */
    Curl_hash_clean(&hostname_cache);
    host_cache_initialized = 0;
  }
}
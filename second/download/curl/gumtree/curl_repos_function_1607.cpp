struct curl_hash *Curl_global_host_cache_init(void)
{
  int rc = 0;
  if(!host_cache_initialized) {
    rc = Curl_hash_init(&hostname_cache, 7, Curl_hash_str,
                        Curl_str_key_compare, freednsentry);
    if(!rc)
      host_cache_initialized = 1;
  }
  return rc?NULL:&hostname_cache;
}
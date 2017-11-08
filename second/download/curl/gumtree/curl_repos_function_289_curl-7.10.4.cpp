void Curl_global_host_cache_init(void)
{
  if (!host_cache_initialized) {
    Curl_hash_init(&hostname_cache, 7, Curl_freednsinfo);
    host_cache_initialized = 1;
  }
}
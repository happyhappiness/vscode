struct curl_hash *Curl_global_host_cache_get(void)
{
  return &hostname_cache;
}
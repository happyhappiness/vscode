void curl_easy_cleanup(CURL *curl)
{
  struct SessionHandle *data = (struct SessionHandle *)curl;
  if (!Curl_global_host_cache_use(data)) {
    Curl_hash_destroy(data->hostcache);
  }
  Curl_close(data);
}
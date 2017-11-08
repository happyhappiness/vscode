CURLcode curl_easy_perform(CURL *curl)
{
  struct SessionHandle *data = (struct SessionHandle *)curl;

  if (Curl_global_host_cache_use(data) && data->hostcache != Curl_global_host_cache_get()) {
    if (data->hostcache) {
      Curl_hash_destroy(data->hostcache);
    }
    data->hostcache = Curl_global_host_cache_get();
  }

  if (!data->hostcache) {
    data->hostcache = Curl_hash_alloc(7, Curl_freednsinfo);
  }
  
  return Curl_perform(data);
}
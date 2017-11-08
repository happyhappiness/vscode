static void
hostcache_prune(curl_hash *hostcache, int cache_timeout, int now)
{
  struct hostcache_prune_data user;

  user.cache_timeout = cache_timeout;
  user.now = now;
  
  Curl_hash_clean_with_criterium(hostcache, 
                                 (void *) &user, 
                                 hostcache_timestamp_remove);
}
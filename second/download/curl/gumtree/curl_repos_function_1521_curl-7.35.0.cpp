void Curl_hostcache_clean(struct SessionHandle *data,
                          struct curl_hash *hash)
{
  /* Entries added to the hostcache with the CURLOPT_RESOLVE function are
   * still present in the cache with the inuse counter set to 1. Detect them
   * and cleanup!
   */
  Curl_hash_clean_with_criterium(hash, data, hostcache_inuse);
}
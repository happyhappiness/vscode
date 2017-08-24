{
    /* See whether the returned entry is stale. Done before we release lock */
    struct hostcache_prune_data user;

    time(&user.now);
    user.cache_timeout = data->set.dns_cache_timeout;

    if(hostcache_timestamp_remove(&user, dns)) {
      infof(data, "Hostname in DNS cache was stale, zapped\n");
      dns = NULL; /* the memory deallocation is being handled by the hash */
      Curl_hash_delete(data->dns.hostcache, entry_id, entry_len+1);
    }
  }
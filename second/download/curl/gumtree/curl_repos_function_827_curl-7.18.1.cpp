static int
remove_entry_if_stale(struct SessionHandle *data, struct Curl_dns_entry *dns)
{
  struct hostcache_prune_data user;

  if( !dns || (data->set.dns_cache_timeout == -1) || !data->dns.hostcache)
    /* cache forever means never prune, and NULL hostcache means
       we can't do it */
    return 0;

  time(&user.now);
  user.cache_timeout = data->set.dns_cache_timeout;

  if( !hostcache_timestamp_remove(&user,dns) )
    return 0;

  Curl_hash_clean_with_criterium(data->dns.hostcache,
                                 (void *) &user,
                                 hostcache_timestamp_remove);

  return 1;
}
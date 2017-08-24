{
  char *entry_id;
  size_t entry_len;
  struct Curl_dns_entry *dns;
  struct Curl_dns_entry *dns2;

  /* Create an entry id, based upon the hostname and port */
  entry_id = create_hostcache_id(hostname, port);
  /* If we can't create the entry id, fail */
  if(!entry_id)
    return NULL;
  entry_len = strlen(entry_id);

  /* Create a new cache entry */
  dns = calloc(1, sizeof(struct Curl_dns_entry));
  if(!dns) {
    free(entry_id);
    return NULL;
  }

  dns->inuse = 1;   /* the cache has the first reference */
  dns->addr = addr; /* this is the address(es) */
  time(&dns->timestamp);
  if(dns->timestamp == 0)
    dns->timestamp = 1;   /* zero indicates CURLOPT_RESOLVE entry */

  /* Store the resolved data in our DNS cache. */
  dns2 = Curl_hash_add(data->dns.hostcache, entry_id, entry_len+1,
                       (void *)dns);
  if(!dns2) {
    free(dns);
    free(entry_id);
    return NULL;
  }

  dns = dns2;
  dns->inuse++;         /* mark entry as in-use */

  /* free the allocated entry_id */
  free(entry_id);

  return dns;
}
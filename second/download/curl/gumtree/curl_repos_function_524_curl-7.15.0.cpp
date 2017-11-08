struct Curl_dns_entry *
Curl_cache_addr(struct SessionHandle *data,
                Curl_addrinfo *addr,
                char *hostname,
                int port)
{
  char *entry_id;
  size_t entry_len;
  struct Curl_dns_entry *dns;
  struct Curl_dns_entry *dns2;
  time_t now;

  /* Create an entry id, based upon the hostname and port */
  entry_id = create_hostcache_id(hostname, port);
  /* If we can't create the entry id, fail */
  if (!entry_id)
    return NULL;
  entry_len = strlen(entry_id);

  /* Create a new cache entry */
  dns = (struct Curl_dns_entry *) malloc(sizeof(struct Curl_dns_entry));
  if (!dns) {
    free(entry_id);
    return NULL;
  }

  dns->inuse = 0;   /* init to not used */
  dns->addr = addr; /* this is the address(es) */

  /* Store the resolved data in our DNS cache. This function may return a
     pointer to an existing struct already present in the hash, and it may
     return the same argument we pass in. Make no assumptions. */
  dns2 = Curl_hash_add(data->hostcache, entry_id, entry_len+1, (void *)dns);
  if(!dns2) {
    /* Major badness, run away. */
    free(dns);
    free(entry_id);
    return NULL;
  }
  time(&now);
  dns = dns2;

  dns->timestamp = now; /* used now */
  dns->inuse++;         /* mark entry as in-use */

  /* free the allocated entry_id again */
  free(entry_id);

  return dns;
}
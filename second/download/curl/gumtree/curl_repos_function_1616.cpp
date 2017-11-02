struct Curl_dns_entry *
Curl_fetch_addr(struct connectdata *conn,
                const char *hostname,
                int port)
{
  char *entry_id = NULL;
  struct Curl_dns_entry *dns = NULL;
  size_t entry_len;
  struct SessionHandle *data = conn->data;
  int stale;

  /* Create an entry id, based upon the hostname and port */
  entry_id = create_hostcache_id(hostname, port);
  /* If we can't create the entry id, fail */
  if(!entry_id)
    return dns;

  entry_len = strlen(entry_id);

  /* See if its already in our dns cache */
  dns = Curl_hash_pick(data->dns.hostcache, entry_id, entry_len+1);

  /* free the allocated entry_id again */
  free(entry_id);

  /* See whether the returned entry is stale. Done before we release lock */
  stale = remove_entry_if_stale(data, dns);
  if(stale) {
    infof(data, "Hostname in DNS cache was stale, zapped\n");
    dns = NULL; /* the memory deallocation is being handled by the hash */
  }

  return dns;
}
CURLcode Curl_loadhostpairs(struct SessionHandle *data)
{
  struct curl_slist *hostp;
  char hostname[256];
  char address[256];
  int port;

  for(hostp = data->change.resolve; hostp; hostp = hostp->next ) {
    if(!hostp->data)
      continue;
    if(hostp->data[0] == '-') {
      /* TODO: mark an entry for removal */
    }
    else if(3 == sscanf(hostp->data, "%255[^:]:%d:%255s", hostname, &port,
                        address)) {
      struct Curl_dns_entry *dns;
      Curl_addrinfo *addr;
      char *entry_id;
      size_t entry_len;

      addr = Curl_str2addr(address, port);
      if(!addr) {
        infof(data, "Resolve %s found illegal!\n", hostp->data);
        continue;
      }

      /* Create an entry id, based upon the hostname and port */
      entry_id = create_hostcache_id(hostname, port);
      /* If we can't create the entry id, fail */
      if(!entry_id) {
        Curl_freeaddrinfo(addr);
        return CURLE_OUT_OF_MEMORY;
      }

      entry_len = strlen(entry_id);

      if(data->share)
        Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

      /* See if its already in our dns cache */
      dns = Curl_hash_pick(data->dns.hostcache, entry_id, entry_len+1);

      /* free the allocated entry_id again */
      free(entry_id);

      if(!dns)
        /* if not in the cache already, put this host in the cache */
        dns = Curl_cache_addr(data, addr, hostname, port);
      else
        /* this is a duplicate, free it again */
        Curl_freeaddrinfo(addr);

      if(data->share)
        Curl_share_unlock(data, CURL_LOCK_DATA_DNS);

      if(!dns) {
        Curl_freeaddrinfo(addr);
        return CURLE_OUT_OF_MEMORY;
      }
      infof(data, "Added %s:%d:%s to DNS cache\n",
            hostname, port, address);
    }
  }
  data->change.resolve = NULL; /* dealt with now */

  return CURLE_OK;
}
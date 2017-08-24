r(hostp = data->change.resolve; hostp; hostp = hostp->next) {
    if(!hostp->data)
      continue;
    if(hostp->data[0] == '-') {
      char *entry_id;
      size_t entry_len;

      if(2 != sscanf(hostp->data + 1, "%255[^:]:%d", hostname, &port)) {
        infof(data, "Couldn't parse CURLOPT_RESOLVE removal entry '%s'!\n",
              hostp->data);
        continue;
      }

      /* Create an entry id, based upon the hostname and port */
      entry_id = create_hostcache_id(hostname, port);
      /* If we can't create the entry id, fail */
      if(!entry_id) {
        return CURLE_OUT_OF_MEMORY;
      }

      entry_len = strlen(entry_id);

      if(data->share)
        Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

      /* delete entry, ignore if it didn't exist */
      Curl_hash_delete(data->dns.hostcache, entry_id, entry_len+1);

      if(data->share)
        Curl_share_unlock(data, CURL_LOCK_DATA_DNS);

      /* free the allocated entry_id again */
      free(entry_id);
    }
    else {
      struct Curl_dns_entry *dns;
      Curl_addrinfo *addr;
      char *entry_id;
      size_t entry_len;

      if(3 != sscanf(hostp->data, "%255[^:]:%d:%255s", hostname, &port,
                     address)) {
        infof(data, "Couldn't parse CURLOPT_RESOLVE entry '%s'!\n",
              hostp->data);
        continue;
      }

      addr = Curl_str2addr(address, port);
      if(!addr) {
        infof(data, "Address in '%s' found illegal!\n", hostp->data);
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

      if(!dns) {
        /* if not in the cache already, put this host in the cache */
        dns = Curl_cache_addr(data, addr, hostname, port);
        if(dns) {
          dns->timestamp = 0; /* mark as added by CURLOPT_RESOLVE */
          /* release the returned reference; the cache itself will keep the
           * entry alive: */
          dns->inuse--;
        }
      }
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
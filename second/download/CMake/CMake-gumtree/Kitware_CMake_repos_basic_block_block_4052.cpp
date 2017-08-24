{
      infof(data, "Hostname in DNS cache was stale, zapped\n");
      dns = NULL; /* the memory deallocation is being handled by the hash */
      Curl_hash_delete(data->dns.hostcache, entry_id, entry_len+1);
    }
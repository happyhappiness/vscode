{
        /* if not in the cache already, put this host in the cache */
        dns = Curl_cache_addr(data, addr, hostname, port);
        if(dns) {
          dns->timestamp = 0; /* mark as added by CURLOPT_RESOLVE */
          /* release the returned reference; the cache itself will keep the
           * entry alive: */
          dns->inuse--;
        }
      }
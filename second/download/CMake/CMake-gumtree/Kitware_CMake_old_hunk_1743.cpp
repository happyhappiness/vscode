  return id;

}



/* Macro to save redundant free'ing of entry_id */

#define _hostcache_return(__v) \

{ \

  free(entry_id); \

  return (__v); \

}



Curl_addrinfo *Curl_resolv(struct SessionHandle *data,

                           char *hostname,

                           int port,

                           char **bufp)

{

  char *entry_id = NULL;

  struct curl_dns_cache_entry *p = NULL;

  ssize_t entry_len;

  time_t now;



  /* If the host cache timeout is 0, we don't do DNS cach'ing

     so fall through */

  if (data->set.dns_cache_timeout == 0) {

    return Curl_getaddrinfo(data, hostname, port, bufp);

  }



  /* Create an entry id, based upon the hostname and port */

  entry_len = strlen(hostname);

  entry_id = _create_hostcache_id(hostname, port, &entry_len);

  /* If we can't create the entry id, don't cache, just fall-through

     to the plain Curl_getaddrinfo() */

  if (!entry_id) {

    return Curl_getaddrinfo(data, hostname, port, bufp);

  }

  

  time(&now);

  /* See if its already in our dns cache */

  if (entry_id && curl_hash_find(data->hostcache, entry_id, entry_len+1, (void **) &p)) {

    /* Do we need to check for a cache timeout? */

    if (data->set.dns_cache_timeout != -1) {

      /* Return if the entry has not timed out */

      if ((now - p->timestamp) < data->set.dns_cache_timeout) {

        _hostcache_return(p->addr);

      }

    }

    else {

      _hostcache_return(p->addr);

    }

  }



  /* Create a new cache entry */

  p = (struct curl_dns_cache_entry *) malloc(sizeof(struct curl_dns_cache_entry));

  if (!p) {

   _hostcache_return(NULL);

  }



  p->addr = Curl_getaddrinfo(data, hostname, port, bufp);

  if (!p->addr) {

    free(p);

    _hostcache_return(NULL);

  }

  p->timestamp = now;



  /* Save it in our host cache */

  curl_hash_update(data->hostcache, entry_id, entry_len+1, (const void *) p);



  _hostcache_return(p->addr);

}



/*


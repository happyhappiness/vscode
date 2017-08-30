  return id;

}



struct hostcache_prune_data {

  int cache_timeout;

  int now;

};



static int

hostcache_timestamp_remove(void *datap, void *hc)

{

  struct hostcache_prune_data *data = 

    (struct hostcache_prune_data *) datap;

  struct Curl_dns_entry *c = (struct Curl_dns_entry *) hc;

  

  if ((data->now - c->timestamp < data->cache_timeout) ||

      c->inuse) {

    /* please don't remove */

    return 0;

  }

  

  /* fine, remove */

  return 1;

}



static void

hostcache_prune(curl_hash *hostcache, int cache_timeout, int now)

{

  struct hostcache_prune_data user;



  user.cache_timeout = cache_timeout;

  user.now = now;

  

  Curl_hash_clean_with_criterium(hostcache, 

                                 (void *) &user, 

                                 hostcache_timestamp_remove);

}



#if defined(MALLOCDEBUG) && defined(AGGRESIVE_TEST)

/* Called from Curl_done() to check that there's no DNS cache entry with

   a non-zero counter left. */

void Curl_scan_cache_used(void *user, void *ptr)

{

  struct Curl_dns_entry *e = ptr;

  (void)user; /* prevent compiler warning */

  if(e->inuse) {

    fprintf(stderr, "*** WARNING: locked DNS cache entry detected: %s\n",

            e->entry_id);

    /* perform a segmentation fault to draw attention */

    *(void **)0 = 0;

  }

}

#endif



/* Macro to save redundant free'ing of entry_id */

#define HOSTCACHE_RETURN(dns) \

{ \

  free(entry_id); \

  return dns; \

}



#ifdef HAVE_SIGSETJMP

/* Beware this is a global and unique instance */

sigjmp_buf curl_jmpenv;

#endif



struct Curl_dns_entry *Curl_resolv(struct SessionHandle *data,

                                   char *hostname,

                                   int port)

{

  char *entry_id = NULL;

  struct Curl_dns_entry *dns = NULL;

  ssize_t entry_len;

  time_t now;

  char *bufp;



#ifdef HAVE_SIGSETJMP

  /* this allows us to time-out from the name resolver, as the timeout

     will generate a signal and we will siglongjmp() from that here */

  if(!data->set.no_signal && sigsetjmp(curl_jmpenv, 1)) {

    /* this is coming from a siglongjmp() */

    failf(data, "name lookup time-outed");

    return NULL;

  }

#endif



  /* Create an entry id, based upon the hostname and port */

  entry_len = strlen(hostname);

  entry_id = create_hostcache_id(hostname, port, &entry_len);

  /* If we can't create the entry id, fail */

  if (!entry_id)

    return NULL;

  

  /* See if its already in our dns cache */

  dns = Curl_hash_pick(data->hostcache, entry_id, entry_len+1);



  if (!dns) {

    Curl_addrinfo *addr = my_getaddrinfo(data, hostname, port, &bufp);

    

    if (!addr) {

      HOSTCACHE_RETURN(NULL);

    }



    /* Create a new cache entry */

    dns = (struct Curl_dns_entry *) malloc(sizeof(struct Curl_dns_entry));

    if (!dns) {

      Curl_freeaddrinfo(addr);

      HOSTCACHE_RETURN(NULL);

    }



    dns->inuse = 0;

    dns->addr = addr;

    /* Save it in our host cache */

    Curl_hash_add(data->hostcache, entry_id, entry_len+1, (const void *) dns);

  }

  time(&now);



  dns->timestamp = now;

  dns->inuse++;         /* mark entry as in-use */

#ifdef MALLOCDEBUG

  dns->entry_id = entry_id;

#endif



  /* Remove outdated and unused entries from the hostcache */

  hostcache_prune(data->hostcache, 

                  data->set.dns_cache_timeout, 

                  now);



  HOSTCACHE_RETURN(dns);

}



/*


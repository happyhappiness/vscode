{
    struct ResolverResults *res = NULL;
    free(conn->async.hostname);
    conn->async.hostname = bufp;
    conn->async.port = port;
    conn->async.done = FALSE;   /* not done */
    conn->async.status = 0;     /* clear */
    conn->async.dns = NULL;     /* clear */
    res = calloc(sizeof(struct ResolverResults), 1);
    if(!res) {
      free(conn->async.hostname);
      conn->async.hostname = NULL;
      return NULL;
    }
    conn->async.os_specific = res;

    /* initial status - failed */
    res->last_status = ARES_ENOTFOUND;
#ifdef ENABLE_IPV6 /* CURLRES_IPV6 */
    if(family == PF_UNSPEC) {
      if(Curl_ipv6works()) {
        res->num_pending = 2;

        /* areschannel is already setup in the Curl_open() function */
        ares_gethostbyname((ares_channel)data->state.resolver, hostname,
                            PF_INET, query_completed_cb, conn);
        ares_gethostbyname((ares_channel)data->state.resolver, hostname,
                            PF_INET6, query_completed_cb, conn);
      }
      else {
        res->num_pending = 1;

        /* areschannel is already setup in the Curl_open() function */
        ares_gethostbyname((ares_channel)data->state.resolver, hostname,
                            PF_INET, query_completed_cb, conn);
      }
    }
    else
#endif /* CURLRES_IPV6 */
    {
      res->num_pending = 1;

      /* areschannel is already setup in the Curl_open() function */
      ares_gethostbyname((ares_channel)data->state.resolver, hostname, family,
                         query_completed_cb, conn);
    }

    *waitp = 1; /* expect asynchronous response */
  }
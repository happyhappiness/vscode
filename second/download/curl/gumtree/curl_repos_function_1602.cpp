Curl_addrinfo *Curl_resolver_getaddrinfo(struct connectdata *conn,
                                         const char *hostname,
                                         int port,
                                         int *waitp)
{
  char *bufp;
  struct SessionHandle *data = conn->data;
  struct in_addr in;
  int family = PF_INET;
#ifdef ENABLE_IPV6 /* CURLRES_IPV6 */
  struct in6_addr in6;
#endif /* CURLRES_IPV6 */

  *waitp = 0; /* default to synchronous response */

  /* First check if this is an IPv4 address string */
  if(Curl_inet_pton(AF_INET, hostname, &in) > 0) {
    /* This is a dotted IP address 123.123.123.123-style */
    return Curl_ip2addr(AF_INET, &in, hostname, port);
  }

#ifdef ENABLE_IPV6 /* CURLRES_IPV6 */
  /* Otherwise, check if this is an IPv6 address string */
  if(Curl_inet_pton (AF_INET6, hostname, &in6) > 0)
    /* This must be an IPv6 address literal.  */
    return Curl_ip2addr(AF_INET6, &in6, hostname, port);

  switch(conn->ip_version) {
  default:
#if ARES_VERSION >= 0x010601
    family = PF_UNSPEC; /* supported by c-ares since 1.6.1, so for older
                           c-ares versions this just falls through and defaults
                           to PF_INET */
    break;
#endif
  case CURL_IPRESOLVE_V4:
    family = PF_INET;
    break;
  case CURL_IPRESOLVE_V6:
    family = PF_INET6;
    break;
  }
#endif /* CURLRES_IPV6 */

  bufp = strdup(hostname);
  if(bufp) {
    struct ResolverResults *res = NULL;
    Curl_safefree(conn->async.hostname);
    conn->async.hostname = bufp;
    conn->async.port = port;
    conn->async.done = FALSE;   /* not done */
    conn->async.status = 0;     /* clear */
    conn->async.dns = NULL;     /* clear */
    res = calloc(sizeof(struct ResolverResults),1);
    if(!res) {
      Curl_safefree(conn->async.hostname);
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
  return NULL; /* no struct yet */
}
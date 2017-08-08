{
  struct addrinfo hints;
  struct in_addr in;
  Curl_addrinfo *res;
  int error;
  char sbuf[12];
  int pf = PF_INET;
#ifdef CURLRES_IPV6
  struct in6_addr in6;
#endif /* CURLRES_IPV6 */

  *waitp = 0; /* default to synchronous response */

#ifndef USE_RESOLVE_ON_IPS
  /* First check if this is an IPv4 address string */
  if(Curl_inet_pton(AF_INET, hostname, &in) > 0)
    /* This is a dotted IP address 123.123.123.123-style */
    return Curl_ip2addr(AF_INET, &in, hostname, port);

#ifdef CURLRES_IPV6
  /* check if this is an IPv6 address string */
  if(Curl_inet_pton(AF_INET6, hostname, &in6) > 0)
    /* This is an IPv6 address literal */
    return Curl_ip2addr(AF_INET6, &in6, hostname, port);
#endif /* CURLRES_IPV6 */
#endif /* !USE_RESOLVE_ON_IPS */

#ifdef CURLRES_IPV6
  /*
   * Check if a limited name resolve has been requested.
   */
  switch(conn->ip_version) {
  case CURL_IPRESOLVE_V4:
    pf = PF_INET;
    break;
  case CURL_IPRESOLVE_V6:
    pf = PF_INET6;
    break;
  default:
    pf = PF_UNSPEC;
    break;
  }

  if((pf != PF_INET) && !Curl_ipv6works())
    /* The stack seems to be a non-IPv6 one */
    pf = PF_INET;
#endif /* CURLRES_IPV6 */

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = pf;
  hints.ai_socktype = conn->socktype;

  snprintf(sbuf, sizeof(sbuf), "%d", port);

  /* fire up a new resolver thread! */
  if(init_resolve_thread(conn, hostname, port, &hints)) {
    *waitp = 1; /* expect asynchronous response */
    return NULL;
  }

  /* fall-back to blocking version */
  infof(conn->data, "init_resolve_thread() failed for %s; %s\n",
        hostname, Curl_strerror(conn, ERRNO));

  error = Curl_getaddrinfo_ex(hostname, sbuf, &hints, &res);
  if(error) {
    infof(conn->data, "getaddrinfo() failed for %s:%d; %s\n",
          hostname, port, Curl_strerror(conn, SOCKERRNO));
    return NULL;
  }
  else {
    Curl_addrinfo_set_port(res, port);
  }

  return res;
}
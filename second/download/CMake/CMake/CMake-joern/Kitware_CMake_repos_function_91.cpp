Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
                                const char *hostname,
                                int port,
                                int *waitp)
{
  struct addrinfo hints;
  Curl_addrinfo *res;
  int error;
  char sbuf[12];
  char *sbufptr = NULL;
#ifndef USE_RESOLVE_ON_IPS
  char addrbuf[128];
#endif
  int pf;
#if !defined(CURL_DISABLE_VERBOSE_STRINGS)
  struct Curl_easy *data = conn->data;
#endif

  *waitp = 0; /* synchronous response only */

  /* Check if a limited name resolve has been requested */
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

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = pf;
  hints.ai_socktype = conn->socktype;

#ifndef USE_RESOLVE_ON_IPS
  /*
   * The AI_NUMERICHOST must not be set to get synthesized IPv6 address from
   * an IPv4 address on iOS and Mac OS X.
   */
  if((1 == Curl_inet_pton(AF_INET, hostname, addrbuf)) ||
     (1 == Curl_inet_pton(AF_INET6, hostname, addrbuf))) {
    /* the given address is numerical only, prevent a reverse lookup */
    hints.ai_flags = AI_NUMERICHOST;
  }
#endif

  if(port) {
    snprintf(sbuf, sizeof(sbuf), "%d", port);
    sbufptr=sbuf;
  }

  error = Curl_getaddrinfo_ex(hostname, sbufptr, &hints, &res);
  if(error) {
    infof(data, "getaddrinfo(3) failed for %s:%d\n", hostname, port);
    return NULL;
  }

  if(port) {
    Curl_addrinfo_set_port(res, port);
  }

  dump_addrinfo(conn, res);

  return res;
}
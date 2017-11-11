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
  char addrbuf[128];
  int pf;
  struct SessionHandle *data = conn->data;

  *waitp = 0; /* synchronous response only */

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
    /* the stack seems to be a non-ipv6 one */
    pf = PF_INET;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = pf;
  hints.ai_socktype = conn->socktype;

  if((1 == Curl_inet_pton(AF_INET, hostname, addrbuf)) ||
     (1 == Curl_inet_pton(AF_INET6, hostname, addrbuf))) {
    /* the given address is numerical only, prevent a reverse lookup */
    hints.ai_flags = AI_NUMERICHOST;
  }

  if(port) {
    snprintf(sbuf, sizeof(sbuf), "%d", port);
    sbufptr=sbuf;
  }
  error = Curl_getaddrinfo_ex(hostname, sbufptr, &hints, &res);
  if(error) {
    infof(data, "getaddrinfo(3) failed for %s:%d\n", hostname, port);
    return NULL;
  }

  dump_addrinfo(conn, res);

  return res;
}
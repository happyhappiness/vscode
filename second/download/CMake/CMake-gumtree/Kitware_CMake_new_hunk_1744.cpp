 * memory we need to free after use. That meory *MUST* be freed with
 * Curl_freeaddrinfo(), nothing else.
 */
static Curl_addrinfo *my_getaddrinfo(struct SessionHandle *data,
                                     char *hostname,
                                     int port,
                                     char **bufp)
{
  struct addrinfo hints, *res;
  int error;
  char sbuf[NI_MAXSERV];
  int s, pf = PF_UNSPEC;

  /* see if we have an IPv6 stack */
  s = socket(PF_INET6, SOCK_DGRAM, 0);
  if (s < 0)
    /* Some non-IPv6 stacks have been found to make very slow name resolves
     * when PF_UNSPEC is used, so thus we switch to a mere PF_INET lookup if
     * the stack seems to be a non-ipv6 one. */
    pf = PF_INET;
  else
    /* This seems to be an IPv6-capable stack, use PF_UNSPEC for the widest
     * possible checks. And close the socket again.
     */
    sclose(s);
 
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = pf;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_CANONNAME;
  snprintf(sbuf, sizeof(sbuf), "%d", port);
  error = getaddrinfo(hostname, sbuf, &hints, &res);
  if (error) {
    infof(data, "getaddrinfo(3) failed for %s:%d\n", hostname, port);    
    return NULL;
  }
  *bufp=(char *)res; /* make it point to the result struct */

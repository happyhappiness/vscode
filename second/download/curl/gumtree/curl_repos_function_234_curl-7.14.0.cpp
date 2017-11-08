Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
                                char *hostname,
                                int port,
                                int *waitp)
{
  struct addrinfo hints, *res;
  int error;
  char sbuf[NI_MAXSERV];
  curl_socket_t s;
  int pf;
  struct SessionHandle *data = conn->data;

  *waitp = FALSE; /* default to synch response */

  /* see if we have an IPv6 stack */
  s = socket(PF_INET6, SOCK_DGRAM, 0);
  if (s == CURL_SOCKET_BAD) {
    /* Some non-IPv6 stacks have been found to make very slow name resolves
     * when PF_UNSPEC is used, so thus we switch to a mere PF_INET lookup if
     * the stack seems to be a non-ipv6 one. */

    pf = PF_INET;
  }
  else {
    /* This seems to be an IPv6-capable stack, use PF_UNSPEC for the widest
     * possible checks. And close the socket again.
     */
    sclose(s);

    /*
     * Check if a more limited name resolve has been requested.
     */
    switch(data->set.ip_version) {
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
  }

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = pf;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_CANONNAME;
  itoa(port, sbuf, 10);

  /* fire up a new resolver thread! */
  if (init_resolve_thread(conn, hostname, port, &hints)) {
    *waitp = TRUE;  /* please wait for the response */
    return NULL;
  }

  /* fall-back to blocking version */
  infof(data, "init_resolve_thread() failed for %s; %s\n",
        hostname, Curl_strerror(conn,GetLastError()));

  error = getaddrinfo(hostname, sbuf, &hints, &res);
  if (error) {
    infof(data, "getaddrinfo() failed for %s:%d; %s\n",
          hostname, port, Curl_strerror(conn,WSAGetLastError()));
    return NULL;
  }
  return res;
}
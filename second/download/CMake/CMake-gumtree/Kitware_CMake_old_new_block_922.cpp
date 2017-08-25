{
  struct addrinfo hints, *res;
  int error;
  char sbuf[NI_MAXSERV];

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = PF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_CANONNAME;
  snprintf(sbuf, sizeof(sbuf), "%d", port);
  error = getaddrinfo(hostname, sbuf, &hints, &res);
  if (error) {
    infof(data, "getaddrinfo(3) failed for %s\n", hostname);    
    return NULL;
  }
  *bufp=(char *)res; /* make it point to the result struct */

  return res;
}
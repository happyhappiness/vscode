void Curl_addrinfo_set_port(Curl_addrinfo *addrinfo, int port)
{
  Curl_addrinfo *ca;
  struct sockaddr_in *addr;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 *addr6;
#endif
  for(ca = addrinfo; ca != NULL; ca = ca->ai_next) {
    switch(ca->ai_family) {
    case AF_INET:
      addr = (void *)ca->ai_addr; /* storage area for this info */
      addr->sin_port = htons((unsigned short)port);
      break;

#ifdef ENABLE_IPV6
    case AF_INET6:
      addr6 = (void *)ca->ai_addr; /* storage area for this info */
      addr6->sin6_port = htons((unsigned short)port);
      break;
#endif
    }
  }
}
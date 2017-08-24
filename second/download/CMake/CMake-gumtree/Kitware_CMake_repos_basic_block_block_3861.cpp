r(ca = addrinfo; ca != NULL; ca = ca->ai_next) {
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
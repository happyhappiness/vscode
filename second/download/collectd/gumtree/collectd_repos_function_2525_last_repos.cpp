static _Bool is_multicast(struct addrinfo const *ai) {
  if (ai->ai_family == AF_INET) {
    struct sockaddr_in *addr = (struct sockaddr_in *)ai->ai_addr;
    return IN_MULTICAST(ntohl(addr->sin_addr.s_addr));
  } else if (ai->ai_family == AF_INET6) {
    struct sockaddr_in6 *addr = (struct sockaddr_in6 *)ai->ai_addr;
    return IN6_IS_ADDR_MULTICAST(&addr->sin6_addr);
  }
  return 0;
}
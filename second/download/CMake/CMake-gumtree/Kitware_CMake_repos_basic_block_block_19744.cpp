{

  struct sockaddr_dl* sa_addr;
  int sockfd;
  int i;
  struct arpreq arpreq;

  /* This appears to only work as root */
  sa_addr = (struct sockaddr_dl*)(ent->ifa_addr);
  memcpy(address->phys_addr, LLADDR(sa_addr), sizeof(address->phys_addr));
  for (i = 0; i < sizeof(address->phys_addr); i++) {
    if (address->phys_addr[i] != 0)
      return 0;
  }
  memset(&arpreq, 0, sizeof(arpreq));
  if (address->address.address4.sin_family == AF_INET) {
    struct sockaddr_in* sin = ((struct sockaddr_in*)&arpreq.arp_pa);
    sin->sin_addr.s_addr = address->address.address4.sin_addr.s_addr;
  } else if (address->address.address4.sin_family == AF_INET6) {
    struct sockaddr_in6* sin = ((struct sockaddr_in6*)&arpreq.arp_pa);
    memcpy(sin->sin6_addr.s6_addr,
           address->address.address6.sin6_addr.s6_addr,
           sizeof(address->address.address6.sin6_addr.s6_addr));
  } else {
    return 0;
  }

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
    return -errno;

  if (ioctl(sockfd, SIOCGARP, (char*)&arpreq) == -1) {
    uv__close(sockfd);
    return -errno;
  }
  memcpy(address->phys_addr, arpreq.arp_ha.sa_data, sizeof(address->phys_addr));
  uv__close(sockfd);
  return 0;
}
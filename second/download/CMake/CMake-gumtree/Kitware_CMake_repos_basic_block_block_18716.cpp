{
  struct ifaddrs* addrs;
  struct ifaddrs* ent;
  uv_interface_address_t* address;
  int i;

  if (getifaddrs(&addrs) != 0)
    return -errno;

  *count = 0;

  /* Count the number of interfaces */
  for (ent = addrs; ent != NULL; ent = ent->ifa_next) {
    if (uv__ifaddr_exclude(ent))
      continue;
    (*count)++;
  }

  *addresses = uv__malloc(*count * sizeof(**addresses));

  if (*addresses == NULL) {
    freeifaddrs(addrs);
    return -ENOMEM;
  }

  address = *addresses;

  for (ent = addrs; ent != NULL; ent = ent->ifa_next) {
    if (uv__ifaddr_exclude(ent))
      continue;

    address->name = uv__strdup(ent->ifa_name);

    if (ent->ifa_addr->sa_family == AF_INET6) {
      address->address.address6 = *((struct sockaddr_in6*) ent->ifa_addr);
    } else {
      address->address.address4 = *((struct sockaddr_in*) ent->ifa_addr);
    }

    if (ent->ifa_netmask->sa_family == AF_INET6) {
      address->netmask.netmask6 = *((struct sockaddr_in6*) ent->ifa_netmask);
    } else {
      address->netmask.netmask4 = *((struct sockaddr_in*) ent->ifa_netmask);
    }

    address->is_internal = !!(ent->ifa_flags & IFF_LOOPBACK);

    address++;
  }

  /* Fill in physical addresses for each interface */
  for (ent = addrs; ent != NULL; ent = ent->ifa_next) {
    if (uv__ifaddr_exclude(ent))
      continue;

    address = *addresses;

    for (i = 0; i < *count; i++) {
      if (strcmp(address->name, ent->ifa_name) == 0) {
#if defined(__CYGWIN__) || defined(__MSYS__)
        memset(address->phys_addr, 0, sizeof(address->phys_addr));
#else
        struct sockaddr_dl* sa_addr;
        sa_addr = (struct sockaddr_dl*)(ent->ifa_addr);
        memcpy(address->phys_addr, LLADDR(sa_addr), sizeof(address->phys_addr));
#endif
      }
      address++;
    }
  }

  freeifaddrs(addrs);

  return 0;
}
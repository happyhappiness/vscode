{
  uv_interface_address_t* address;
  struct ifaddrs* addrs;
  struct ifaddrs* ent;
  int i;

  if (getifaddrs(&addrs))
    return -errno;

  *count = 0;

  /* Count the number of interfaces */
  for (ent = addrs; ent != NULL; ent = ent->ifa_next) {
    if (uv__ifaddr_exclude(ent))
      continue;
    (*count)++;
  }

  *addresses = uv__malloc(*count * sizeof(**addresses));
  if (!(*addresses)) {
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

    address->is_internal = !!((ent->ifa_flags & IFF_PRIVATE) ||
                           (ent->ifa_flags & IFF_LOOPBACK));

    uv__set_phys_addr(address, ent);
    address++;
  }

  freeifaddrs(addrs);

  return 0;
}
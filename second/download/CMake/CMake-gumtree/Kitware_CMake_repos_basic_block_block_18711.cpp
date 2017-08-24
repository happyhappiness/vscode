{
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
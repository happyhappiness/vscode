{
  uv_interface_address_t* address;
  int sockfd;
  int maxsize;
  __net_ifconf6header_t ifc;
  __net_ifconf6entry_t* ifr;
  __net_ifconf6entry_t* p;
  __net_ifconf6entry_t flg;

  *count = 0;
  /* Assume maximum buffer size allowable */
  maxsize = 16384;

  if (0 > (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)))
    return -errno;

  ifc.__nif6h_version = 1;
  ifc.__nif6h_buflen = maxsize;
  ifc.__nif6h_buffer = uv__calloc(1, maxsize);;

  if (ioctl(sockfd, SIOCGIFCONF6, &ifc) == -1) {
    uv__close(sockfd);
    return -errno;
  }


  *count = 0;
  ifr = (__net_ifconf6entry_t*)(ifc.__nif6h_buffer);
  while ((char*)ifr < (char*)ifc.__nif6h_buffer + ifc.__nif6h_buflen) {
    p = ifr;
    ifr = (__net_ifconf6entry_t*)((char*)ifr + ifc.__nif6h_entrylen);

    if (!(p->__nif6e_addr.sin6_family == AF_INET6 ||
          p->__nif6e_addr.sin6_family == AF_INET))
      continue;

    if (!(p->__nif6e_flags & _NIF6E_FLAGS_ON_LINK_ACTIVE))
      continue;

    ++(*count);
  }

  /* Alloc the return interface structs */
  *addresses = uv__malloc(*count * sizeof(uv_interface_address_t));
  if (!(*addresses)) {
    uv__close(sockfd);
    return -ENOMEM;
  }
  address = *addresses;

  ifr = (__net_ifconf6entry_t*)(ifc.__nif6h_buffer);
  while ((char*)ifr < (char*)ifc.__nif6h_buffer + ifc.__nif6h_buflen) {
    p = ifr;
    ifr = (__net_ifconf6entry_t*)((char*)ifr + ifc.__nif6h_entrylen);

    if (!(p->__nif6e_addr.sin6_family == AF_INET6 ||
          p->__nif6e_addr.sin6_family == AF_INET))
      continue;

    if (!(p->__nif6e_flags & _NIF6E_FLAGS_ON_LINK_ACTIVE))
      continue;

    /* All conditions above must match count loop */

    address->name = uv__strdup(p->__nif6e_name);

    if (p->__nif6e_addr.sin6_family == AF_INET6)
      address->address.address6 = *((struct sockaddr_in6*) &p->__nif6e_addr);
    else
      address->address.address4 = *((struct sockaddr_in*) &p->__nif6e_addr);

    /* TODO: Retrieve netmask using SIOCGIFNETMASK ioctl */

    address->is_internal = flg.__nif6e_flags & _NIF6E_FLAGS_LOOPBACK ? 1 : 0;

    address++;
  }

  uv__close(sockfd);
  return 0;
}
{
  IP_ADAPTER_ADDRESSES* win_address_buf;
  ULONG win_address_buf_size;
  IP_ADAPTER_ADDRESSES* adapter;

  uv_interface_address_t* uv_address_buf;
  char* name_buf;
  size_t uv_address_buf_size;
  uv_interface_address_t* uv_address;

  int count;

  int is_vista_or_greater;
  ULONG flags;

  is_vista_or_greater = is_windows_version_or_greater(6, 0, 0, 0);
  if (is_vista_or_greater) {
    flags = GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST |
      GAA_FLAG_SKIP_DNS_SERVER;
  } else {
    /* We need at least XP SP1. */
    if (!is_windows_version_or_greater(5, 1, 1, 0))
      return UV_ENOTSUP;

    flags = GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST |
      GAA_FLAG_SKIP_DNS_SERVER | GAA_FLAG_INCLUDE_PREFIX;
  }


  /* Fetch the size of the adapters reported by windows, and then get the */
  /* list itself. */
  win_address_buf_size = 0;
  win_address_buf = NULL;

  for (;;) {
    ULONG r;

    /* If win_address_buf is 0, then GetAdaptersAddresses will fail with */
    /* ERROR_BUFFER_OVERFLOW, and the required buffer size will be stored in */
    /* win_address_buf_size. */
    r = GetAdaptersAddresses(AF_UNSPEC,
                             flags,
                             NULL,
                             win_address_buf,
                             &win_address_buf_size);

    if (r == ERROR_SUCCESS)
      break;

    uv__free(win_address_buf);

    switch (r) {
      case ERROR_BUFFER_OVERFLOW:
        /* This happens when win_address_buf is NULL or too small to hold */
        /* all adapters. */
        win_address_buf = uv__malloc(win_address_buf_size);
        if (win_address_buf == NULL)
          return UV_ENOMEM;

        continue;

      case ERROR_NO_DATA: {
        /* No adapters were found. */
        uv_address_buf = uv__malloc(1);
        if (uv_address_buf == NULL)
          return UV_ENOMEM;

        *count_ptr = 0;
        *addresses_ptr = uv_address_buf;

        return 0;
      }

      case ERROR_ADDRESS_NOT_ASSOCIATED:
        return UV_EAGAIN;

      case ERROR_INVALID_PARAMETER:
        /* MSDN says:
         *   "This error is returned for any of the following conditions: the
         *   SizePointer parameter is NULL, the Address parameter is not
         *   AF_INET, AF_INET6, or AF_UNSPEC, or the address information for
         *   the parameters requested is greater than ULONG_MAX."
         * Since the first two conditions are not met, it must be that the
         * adapter data is too big.
         */
        return UV_ENOBUFS;

      default:
        /* Other (unspecified) errors can happen, but we don't have any */
        /* special meaning for them. */
        assert(r != ERROR_SUCCESS);
        return uv_translate_sys_error(r);
    }
  }

  /* Count the number of enabled interfaces and compute how much space is */
  /* needed to store their info. */
  count = 0;
  uv_address_buf_size = 0;

  for (adapter = win_address_buf;
       adapter != NULL;
       adapter = adapter->Next) {
    IP_ADAPTER_UNICAST_ADDRESS* unicast_address;
    int name_size;

    /* Interfaces that are not 'up' should not be reported. Also skip */
    /* interfaces that have no associated unicast address, as to avoid */
    /* allocating space for the name for this interface. */
    if (adapter->OperStatus != IfOperStatusUp ||
        adapter->FirstUnicastAddress == NULL)
      continue;

    /* Compute the size of the interface name. */
    name_size = WideCharToMultiByte(CP_UTF8,
                                    0,
                                    adapter->FriendlyName,
                                    -1,
                                    NULL,
                                    0,
                                    NULL,
                                    FALSE);
    if (name_size <= 0) {
      uv__free(win_address_buf);
      return uv_translate_sys_error(GetLastError());
    }
    uv_address_buf_size += name_size;

    /* Count the number of addresses associated with this interface, and */
    /* compute the size. */
    for (unicast_address = (IP_ADAPTER_UNICAST_ADDRESS*)
                           adapter->FirstUnicastAddress;
         unicast_address != NULL;
         unicast_address = unicast_address->Next) {
      count++;
      uv_address_buf_size += sizeof(uv_interface_address_t);
    }
  }

  /* Allocate space to store interface data plus adapter names. */
  uv_address_buf = uv__malloc(uv_address_buf_size);
  if (uv_address_buf == NULL) {
    uv__free(win_address_buf);
    return UV_ENOMEM;
  }

  /* Compute the start of the uv_interface_address_t array, and the place in */
  /* the buffer where the interface names will be stored. */
  uv_address = uv_address_buf;
  name_buf = (char*) (uv_address_buf + count);

  /* Fill out the output buffer. */
  for (adapter = win_address_buf;
       adapter != NULL;
       adapter = adapter->Next) {
    IP_ADAPTER_UNICAST_ADDRESS* unicast_address;
    int name_size;
    size_t max_name_size;

    if (adapter->OperStatus != IfOperStatusUp ||
        adapter->FirstUnicastAddress == NULL)
      continue;

    /* Convert the interface name to UTF8. */
    max_name_size = (char*) uv_address_buf + uv_address_buf_size - name_buf;
    if (max_name_size > (size_t) INT_MAX)
      max_name_size = INT_MAX;
    name_size = WideCharToMultiByte(CP_UTF8,
                                    0,
                                    adapter->FriendlyName,
                                    -1,
                                    name_buf,
                                    (int) max_name_size,
                                    NULL,
                                    FALSE);
    if (name_size <= 0) {
      uv__free(win_address_buf);
      uv__free(uv_address_buf);
      return uv_translate_sys_error(GetLastError());
    }

    /* Add an uv_interface_address_t element for every unicast address. */
    for (unicast_address = (IP_ADAPTER_UNICAST_ADDRESS*)
                           adapter->FirstUnicastAddress;
         unicast_address != NULL;
         unicast_address = unicast_address->Next) {
      struct sockaddr* sa;
      ULONG prefix_len;

      sa = unicast_address->Address.lpSockaddr;

      /* XP has no OnLinkPrefixLength field. */
      if (is_vista_or_greater) {
        prefix_len =
          ((IP_ADAPTER_UNICAST_ADDRESS_LH*) unicast_address)->OnLinkPrefixLength;
      } else {
        /* Prior to Windows Vista the FirstPrefix pointed to the list with
         * single prefix for each IP address assigned to the adapter.
         * Order of FirstPrefix does not match order of FirstUnicastAddress,
         * so we need to find corresponding prefix.
         */
        IP_ADAPTER_PREFIX* prefix;
        prefix_len = 0;

        for (prefix = adapter->FirstPrefix; prefix; prefix = prefix->Next) {
          /* We want the longest matching prefix. */
          if (prefix->Address.lpSockaddr->sa_family != sa->sa_family ||
              prefix->PrefixLength <= prefix_len)
            continue;

          if (address_prefix_match(sa->sa_family, sa,
              prefix->Address.lpSockaddr, prefix->PrefixLength)) {
            prefix_len = prefix->PrefixLength;
          }
        }

        /* If there is no matching prefix information, return a single-host
         * subnet mask (e.g. 255.255.255.255 for IPv4).
         */
        if (!prefix_len)
          prefix_len = (sa->sa_family == AF_INET6) ? 128 : 32;
      }

      memset(uv_address, 0, sizeof *uv_address);

      uv_address->name = name_buf;

      if (adapter->PhysicalAddressLength == sizeof(uv_address->phys_addr)) {
        memcpy(uv_address->phys_addr,
               adapter->PhysicalAddress,
               sizeof(uv_address->phys_addr));
      }

      uv_address->is_internal =
          (adapter->IfType == IF_TYPE_SOFTWARE_LOOPBACK);

      if (sa->sa_family == AF_INET6) {
        uv_address->address.address6 = *((struct sockaddr_in6 *) sa);

        uv_address->netmask.netmask6.sin6_family = AF_INET6;
        memset(uv_address->netmask.netmask6.sin6_addr.s6_addr, 0xff, prefix_len >> 3);
        /* This check ensures that we don't write past the size of the data. */
        if (prefix_len % 8) {
          uv_address->netmask.netmask6.sin6_addr.s6_addr[prefix_len >> 3] =
              0xff << (8 - prefix_len % 8);
        }

      } else {
        uv_address->address.address4 = *((struct sockaddr_in *) sa);

        uv_address->netmask.netmask4.sin_family = AF_INET;
        uv_address->netmask.netmask4.sin_addr.s_addr = (prefix_len > 0) ?
            htonl(0xffffffff << (32 - prefix_len)) : 0;
      }

      uv_address++;
    }

    name_buf += name_size;
  }

  uv__free(win_address_buf);

  *addresses_ptr = uv_address_buf;
  *count_ptr = count;

  return 0;
}
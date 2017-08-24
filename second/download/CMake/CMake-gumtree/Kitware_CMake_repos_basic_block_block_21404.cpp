{
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
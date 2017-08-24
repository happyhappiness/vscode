(uv_ip6_addr(multicast_addr, 0, &addr6) == 0) {
    err = uv__udp_maybe_deferred_bind(handle, AF_INET6, UV_UDP_REUSEADDR);
    if (err)
      return err;
    return uv__udp_set_membership6(handle, &addr6, interface_addr, membership);
  }
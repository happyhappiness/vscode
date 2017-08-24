{
  int optname;
  int err;
  struct ipv6_mreq mreq;
  struct sockaddr_in6 addr6;

  if ((handle->flags & UV_HANDLE_BOUND) && !(handle->flags & UV_HANDLE_IPV6))
    return UV_EINVAL;

  err = uv_udp_maybe_bind(handle,
                          (const struct sockaddr*) &uv_addr_ip6_any_,
                          sizeof(uv_addr_ip6_any_),
                          UV_UDP_REUSEADDR);

  if (err)
    return uv_translate_sys_error(err);

  memset(&mreq, 0, sizeof(mreq));

  if (interface_addr) {
    if (uv_ip6_addr(interface_addr, 0, &addr6))
      return UV_EINVAL;
    mreq.ipv6mr_interface = addr6.sin6_scope_id;
  } else {
    mreq.ipv6mr_interface = 0;
  }

  mreq.ipv6mr_multiaddr = multicast_addr->sin6_addr;

  switch (membership) {
  case UV_JOIN_GROUP:
    optname = IPV6_ADD_MEMBERSHIP;
    break;
  case UV_LEAVE_GROUP:
    optname = IPV6_DROP_MEMBERSHIP;
    break;
  default:
    return UV_EINVAL;
  }

  if (setsockopt(handle->socket,
                 IPPROTO_IPV6,
                 optname,
                 (char*) &mreq,
                 sizeof mreq) == SOCKET_ERROR) {
    return uv_translate_sys_error(WSAGetLastError());
  }

  return 0;
}
{
  int err;
  int optname;
  struct ip_mreq mreq;

  if (handle->flags & UV_HANDLE_IPV6)
    return UV_EINVAL;

  /* If the socket is unbound, bind to inaddr_any. */
  err = uv_udp_maybe_bind(handle,
                          (const struct sockaddr*) &uv_addr_ip4_any_,
                          sizeof(uv_addr_ip4_any_),
                          UV_UDP_REUSEADDR);
  if (err)
    return uv_translate_sys_error(err);

  memset(&mreq, 0, sizeof mreq);

  if (interface_addr) {
    err = uv_inet_pton(AF_INET, interface_addr, &mreq.imr_interface.s_addr);
    if (err)
      return err;
  } else {
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
  }

  mreq.imr_multiaddr.s_addr = multicast_addr->sin_addr.s_addr;

  switch (membership) {
    case UV_JOIN_GROUP:
      optname = IP_ADD_MEMBERSHIP;
      break;
    case UV_LEAVE_GROUP:
      optname = IP_DROP_MEMBERSHIP;
      break;
    default:
      return UV_EINVAL;
  }

  if (setsockopt(handle->socket,
                 IPPROTO_IP,
                 optname,
                 (char*) &mreq,
                 sizeof mreq) == SOCKET_ERROR) {
    return uv_translate_sys_error(WSAGetLastError());
  }

  return 0;
}
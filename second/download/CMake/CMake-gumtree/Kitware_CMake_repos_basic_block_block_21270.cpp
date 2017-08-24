{
  int r;
  int err;
  DWORD no = 0;

  if (handle->flags & UV_HANDLE_BOUND)
    return 0;

  if ((flags & UV_UDP_IPV6ONLY) && addr->sa_family != AF_INET6) {
    /* UV_UDP_IPV6ONLY is supported only for IPV6 sockets */
    return ERROR_INVALID_PARAMETER;
  }

  if (handle->socket == INVALID_SOCKET) {
    SOCKET sock = socket(addr->sa_family, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
      return WSAGetLastError();
    }

    err = uv_udp_set_socket(handle->loop, handle, sock, addr->sa_family);
    if (err) {
      closesocket(sock);
      return err;
    }
  }

  if (flags & UV_UDP_REUSEADDR) {
    DWORD yes = 1;
    /* Set SO_REUSEADDR on the socket. */
    if (setsockopt(handle->socket,
                   SOL_SOCKET,
                   SO_REUSEADDR,
                   (char*) &yes,
                   sizeof yes) == SOCKET_ERROR) {
      err = WSAGetLastError();
      return err;
    }
  }

  if (addr->sa_family == AF_INET6)
    handle->flags |= UV_HANDLE_IPV6;

  if (addr->sa_family == AF_INET6 && !(flags & UV_UDP_IPV6ONLY)) {
    /* On windows IPV6ONLY is on by default. */
    /* If the user doesn't specify it libuv turns it off. */

    /* TODO: how to handle errors? This may fail if there is no ipv4 stack */
    /* available, or when run on XP/2003 which have no support for dualstack */
    /* sockets. For now we're silently ignoring the error. */
    setsockopt(handle->socket,
               IPPROTO_IPV6,
               IPV6_V6ONLY,
               (char*) &no,
               sizeof no);
  }

  r = bind(handle->socket, addr, addrlen);
  if (r == SOCKET_ERROR) {
    return WSAGetLastError();
  }

  handle->flags |= UV_HANDLE_BOUND;

  return 0;
}
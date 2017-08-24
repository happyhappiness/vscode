{
    SOCKET sock;

    /* Cannot set IPv6-only mode on non-IPv6 socket. */
    if ((flags & UV_TCP_IPV6ONLY) && addr->sa_family != AF_INET6)
      return ERROR_INVALID_PARAMETER;

    sock = socket(addr->sa_family, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
      return WSAGetLastError();
    }

    err = uv_tcp_set_socket(handle->loop, handle, sock, addr->sa_family, 0);
    if (err) {
      closesocket(sock);
      return err;
    }
  }
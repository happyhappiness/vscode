(handle->socket == INVALID_SOCKET) {
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
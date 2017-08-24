{
    closesocket(tcp->socket);
    tcp->socket = INVALID_SOCKET;
    tcp->flags |= UV_HANDLE_TCP_SOCKET_CLOSED;
  }
(!(handle->flags & UV_HANDLE_SHARED_TCP_SOCKET) &&
      listen(handle->socket, backlog) == SOCKET_ERROR) {
    return WSAGetLastError();
  }
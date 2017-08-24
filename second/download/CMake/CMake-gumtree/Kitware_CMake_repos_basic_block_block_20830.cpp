{
      closesocket(handle->socket);
      handle->socket = INVALID_SOCKET;
      handle->flags |= UV_HANDLE_TCP_SOCKET_CLOSED;
    }
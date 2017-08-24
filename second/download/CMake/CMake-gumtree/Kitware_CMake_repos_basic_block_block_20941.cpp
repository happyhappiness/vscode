{
  if (!(handle->flags & UV_HANDLE_CONNECTION)) {
    /*
     * We're about to share the socket with another process.  Because
     * this is a listening socket, we assume that the other process will
     * be accepting connections on it.  So, before sharing the socket
     * with another process, we call listen here in the parent process.
     */

    if (!(handle->flags & UV_HANDLE_LISTENING)) {
      if (!(handle->flags & UV_HANDLE_BOUND)) {
        return ERROR_INVALID_PARAMETER;
      }

      if (!(handle->delayed_error)) {
        if (listen(handle->socket, SOMAXCONN) == SOCKET_ERROR) {
          handle->delayed_error = WSAGetLastError();
        }
      }
    }
  }

  if (WSADuplicateSocketW(handle->socket, pid, protocol_info)) {
    return WSAGetLastError();
  }

  handle->flags |= UV_HANDLE_SHARED_TCP_SOCKET;

  return 0;
}
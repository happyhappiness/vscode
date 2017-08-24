(WSADuplicateSocketW(handle->socket, pid, protocol_info)) {
    return WSAGetLastError();
  }
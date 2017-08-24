(ioctlsocket(socket, FIONBIO, &yes) == SOCKET_ERROR) {
    return WSAGetLastError();
  }
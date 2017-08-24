(enable && setsockopt(socket,
                           IPPROTO_TCP,
                           TCP_KEEPALIVE,
                           (const char*)&delay,
                           sizeof delay) == -1) {
    return WSAGetLastError();
  }
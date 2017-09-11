inline int TryBindHost(int start_port, int end_port) {    
    for (int port = start_port; port < end_port; ++port) {
      SockAddr addr("0.0.0.0", port);
      if (bind(sockfd, (sockaddr*)&addr.addr, sizeof(addr.addr)) == 0) {
        return port;
      }
      if (errno != EADDRINUSE) {
        SockError("TryBindHost");
      }
    }
    return -1;
  }
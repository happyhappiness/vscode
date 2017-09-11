inline void Bind(const SockAddr &addr) {
    if (bind(sockfd, (sockaddr*)&addr.addr, sizeof(addr.addr)) == -1) {
      SockError("Bind");
    }
  }
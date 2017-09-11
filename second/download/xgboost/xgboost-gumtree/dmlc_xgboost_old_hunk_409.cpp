   */
  inline void Connect(const SockAddr &addr) {
    if (connect(sockfd, (sockaddr*)&addr.addr, sizeof(addr.addr)) == -1) {
      SockError("Connect", errno);
    }
  }
  /*! \brief close the connection */

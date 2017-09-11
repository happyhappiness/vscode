   */
  inline void Connect(const SockAddr &addr) {
    if (connect(sockfd, (sockaddr*)&addr.addr, sizeof(addr.addr)) == -1) {
      SockError("Connect");
    }
  }
  /*! \brief close the connection */

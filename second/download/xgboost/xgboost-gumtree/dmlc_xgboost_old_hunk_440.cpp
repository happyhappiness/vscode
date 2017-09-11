  inline void Listen(int backlog = 16) {
    listen(sockfd, backlog);
  }
  /*! 
   * \brief bind the socket to an address 
   * \param 3
   */
  inline void Bind(const SockAddr &addr) {
    if (bind(sockfd, (sockaddr*)&addr.addr, sizeof(addr.addr)) == -1) {
      SockError("Bind", errno);
    }
  }
  /*! 
   * \brief connect to an address 
   * \param addr the address to connect to
   */

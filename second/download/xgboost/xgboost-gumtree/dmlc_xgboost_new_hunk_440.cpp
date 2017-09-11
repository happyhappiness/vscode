  inline void Listen(int backlog = 16) {
    listen(sockfd, backlog);
  }
  /*! \brief get a new connection */
  TCPSocket Accept(void) {
    int newfd = accept(sockfd, NULL, NULL);
    if (newfd == -1) {
      SockError("Accept", errno);
    }
    return TCPSocket(newfd);
  }
  /*! 
   * \brief bind the socket to an address 
   * \param addr
   */
  inline void Bind(const SockAddr &addr) {
    if (bind(sockfd, (sockaddr*)&addr.addr, sizeof(addr.addr)) == -1) {
      SockError("Bind", errno);
    }
  }
  /*! 
   * \brief try bind the socket to host, from start_port to end_port
   * \param start_port starting port number to try
   * \param end_port ending port number to try
   * \param out_addr the binding address, if successful
   * \return whether the binding is successful
   */
  inline int TryBindHost(int start_port, int end_port) {    
    for (int port = start_port; port < end_port; ++port) {
      SockAddr addr("0.0.0.0", port);
      if (bind(sockfd, (sockaddr*)&addr.addr, sizeof(addr.addr)) == 0) {
        return port;
      }
      if (errno != EADDRINUSE) {
        SockError("TryBindHost", errno);
      }
    }
    return -1;
  }                      
  /*! 
   * \brief connect to an address 
   * \param addr the address to connect to
   */

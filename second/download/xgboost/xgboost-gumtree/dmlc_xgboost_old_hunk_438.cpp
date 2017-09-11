  /*! \brief the file descriptor of socket */
  int sockfd;
  // constructor
  TCPSocket(void) {}
  // default conversion to int
  inline operator int() const {
    return sockfd;
  }
  /*!
   * \brief start up the socket module
   *   call this before using the sockets
   */

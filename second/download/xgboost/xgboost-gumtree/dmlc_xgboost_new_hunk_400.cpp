  }
  /*! \brief get a new connection */
  TCPSocket Accept(void) {
    sock_t newfd = accept(sockfd, NULL, NULL);
    if (newfd == INVALID_sock_t) {
      SockError("Accept");
    }
    return TCPSocket(newfd);

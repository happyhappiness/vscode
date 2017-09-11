  }
  /*! \brief get a new connection */
  TCPSocket Accept(void) {
    SOCKET newfd = accept(sockfd, NULL, NULL);
    if (newfd == INVALID_SOCKET) {
      SockError("Accept");
    }
    return TCPSocket(newfd);
  }

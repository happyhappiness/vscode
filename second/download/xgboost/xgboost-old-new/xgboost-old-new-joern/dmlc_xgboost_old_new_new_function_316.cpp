TCPSocket Accept(void) {
    int newfd = accept(sockfd, NULL, NULL);
    if (newfd == -1) {
      SockError("Accept", errno);
    }
    return TCPSocket(newfd);
  }
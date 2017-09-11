    if (fcntl(sockfd, F_SETFL, flag) == -1) {
      SockError("SetNonBlock-2", errno);
    }
  }
  /*!
   * \brief perform listen of the socket

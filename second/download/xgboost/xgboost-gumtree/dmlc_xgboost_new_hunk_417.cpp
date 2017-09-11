    if (fcntl(sockfd, F_SETFL, flag) == -1) {
      SockError("SetNonBlock-2", errno);
    }
#endif
  }
  /*!
   * \brief perform listen of the socket

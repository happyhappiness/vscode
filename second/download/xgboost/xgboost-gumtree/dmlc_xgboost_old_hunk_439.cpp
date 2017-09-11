  /*! 
   * \brief set this socket to use async I/O 
   */
  inline void SetAsync(void) {
    if (fcntl(sockfd, fcntl(sockfd, F_GETFL) | O_NONBLOCK) == -1) {
      SockError("SetAsync", errno);
    }
  }
  /*!

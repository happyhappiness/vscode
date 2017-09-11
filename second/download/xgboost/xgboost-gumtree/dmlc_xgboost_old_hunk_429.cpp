  inline static void Finalize(void) {
  }
  /*! 
   * \brief set this socket to use async I/O 
   */
  inline void SetNonBlock(void) {
    if (fcntl(sockfd, fcntl(sockfd, F_GETFL) | O_NONBLOCK) == -1) {
      SockError("SetNonBlock", errno);
    }
  }
  /*!

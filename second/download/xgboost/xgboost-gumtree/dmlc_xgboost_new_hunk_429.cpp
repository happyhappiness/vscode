  inline static void Finalize(void) {
  }
  /*! 
   * \brief set this socket to use non-blocking mode
   * \param non_block whether set it to be non-block, if it is false
   *        it will set it back to block mode
   */
  inline void SetNonBlock(bool non_block) {
    int flag = fcntl(sockfd, F_GETFL, 0);
    if (flag == -1) {
      SockError("SetNonBlock-1", errno);
    }
    if (non_block) {
      flag |= O_NONBLOCK;
    } else {
      flag &= ~O_NONBLOCK;
    }
    if (fcntl(sockfd, F_SETFL, flag) == -1) {
      SockError("SetNonBlock-2", errno);
    }
  }
  /*!

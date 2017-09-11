  /*!
   * \brief enable/disable TCP keepalive
   * \param keepalive whether to set the keep alive option on
   */  
  inline void SetKeepAlive(bool keepalive) {
    int opt = static_cast<int>(keepalive);
    if (setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, reinterpret_cast<char*>(&opt), sizeof(opt)) < 0) {
      Socket::Error("SetKeepAlive");
    }
  }

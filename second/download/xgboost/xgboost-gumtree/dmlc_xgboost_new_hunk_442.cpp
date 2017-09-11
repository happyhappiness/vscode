  inline size_t Send(const void *buf, size_t len, int flag = 0) {
    if (len == 0) return 0;
    ssize_t ret = send(sockfd, buf, len, flag);
    if (ret == -1) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return 0;
      SockError("Send", errno);
    }
    return ret;
  }  
  /*! 
   * \brief receive data using the socket 
   * \param buf the pointer to the buffer
   * \param len the size of the buffer
   * \param flags extra flags
   * \return size of data actually received 
   */
  inline size_t Recv(void *buf, size_t len, int flags = 0) {
    if (len == 0) return 0;    
    ssize_t ret = recv(sockfd, buf, len, flags);
    if (ret == -1) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return 0;
      SockError("Recv", errno);
    }
    return ret;
  } 
  /*!
   * \brief peform block write that will attempt to send all data out
   *    can still return smaller than request when error occurs
   * \param buf the pointer to the buffer
   * \param len the size of the buffer
   * \return size of data actually sent
   */
  inline size_t SendAll(const void *buf_, size_t len) {
    const char *buf = reinterpret_cast<const char*>(buf_);
    size_t ndone = 0;
    while (ndone <  len) {
      ssize_t ret = send(sockfd, buf, len, 0);
      if (ret == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
        SockError("Recv", errno);
      }
      buf += ret;
      ndone += ret;
    }
    return ndone;
  }
  /*!
   * \brief peforma block read that will attempt to read all data
   *    can still return smaller than request when error occurs
   * \param buf_ the buffer pointer
   * \param len length of data to recv
   * \return size of data actually sent
   */
  inline size_t RecvAll(void *buf_, size_t len) {
    char *buf = reinterpret_cast<char*>(buf_);
    size_t ndone = 0;
    while (ndone <  len) {
      ssize_t ret = recv(sockfd, buf, len, MSG_WAITALL);
      if (ret == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
        SockError("Recv", errno);
      }
      if (ret == 0) return ndone;
      buf += ret;
      ndone += ret;
    }
    return ndone;
  }

 private:
  // report an socket error
  inline static void SockError(const char *msg, int errsv) {

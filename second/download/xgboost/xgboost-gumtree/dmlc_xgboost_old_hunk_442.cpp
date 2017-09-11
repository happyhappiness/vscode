  inline size_t Send(const void *buf, size_t len, int flag = 0) {
    if (len == 0) return 0;
    ssize_t ret = send(sockfd, buf, len, flag);
    if (ret == -1) SockError("Send", errno);
    return ret;
  }
  /*! 
   * \brief send data using the socket 
   * \param buf the pointer to the buffer
   * \param len the size of the buffer
   * \param flags extra flags
   * \return size of data actually received 
   */
  inline size_t Recv(void *buf, size_t len, int flags = 0) {
    if (len == 0) return 0;
    ssize_t ret = recv(sockfd, buf, len, flags);
    if (ret == -1) SockError("Recv", errno);
    return ret;
   }
 private:
  // report an socket error
  inline static void SockError(const char *msg, int errsv) {

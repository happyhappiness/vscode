  }  
  /*! 
   * \brief receive data using the socket 
   * \param buf_ the pointer to the buffer
   * \param len the size of the buffer
   * \param flags extra flags
   * \return size of data actually received 
   */
  inline size_t Recv(void *buf_, size_t len, int flags = 0) {
	char *buf = reinterpret_cast<char*>(buf_);
    if (len == 0) return 0;    
    ssize_t ret = recv(sockfd, buf, static_cast<sock_size_t>(len), flags);
    if (ret == -1) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return 0;
      SockError("Recv");

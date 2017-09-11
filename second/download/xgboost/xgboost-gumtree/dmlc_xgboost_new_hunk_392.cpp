   * \param flags extra flags
   * \return size of data actually sent
   */
  inline size_t Send(const void *buf_, size_t len, int flag = 0) {
	const char *buf = reinterpret_cast<const char*>(buf_);
    if (len == 0) return 0;
    ssize_t ret = send(sockfd, buf, static_cast<sock_size_t>(len), flag);
    if (ret == -1) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return 0;
      SockError("Send");

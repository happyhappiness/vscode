   * \return size of data actually sent
   */
  inline size_t Send(const void *buf, size_t len, int flag = 0) {
    if (len == 0) return 0;
    ssize_t ret = send(sockfd, buf, len, flag);
    if (ret == -1) SockError("Send", errno);
    return ret;

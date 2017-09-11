   * \return size of data actually received 
   */
  inline size_t Recv(void *buf, size_t len, int flags = 0) {
    if (len == 0) return 0;
    ssize_t ret = recv(sockfd, buf, len, flags);
    if (ret == -1) SockError("Recv", errno);
    return ret;

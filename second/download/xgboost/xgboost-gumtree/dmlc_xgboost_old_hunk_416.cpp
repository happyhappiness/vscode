   *        it will set it back to block mode
   */
  inline void SetNonBlock(bool non_block) {
    int flag = fcntl(sockfd, F_GETFL, 0);
    if (flag == -1) {
      SockError("SetNonBlock-1", errno);

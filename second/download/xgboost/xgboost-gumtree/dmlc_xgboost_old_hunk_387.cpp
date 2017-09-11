   */
  inline void SetNonBlock(bool non_block) {
#ifdef _WIN32  
	u_long mode = non_block ? 1 : 0;
	if (ioctlsocket(sockfd, FIONBIO, &mode) != NO_ERROR) {
      SockError("SetNonBlock");
	}
#else
    int flag = fcntl(sockfd, F_GETFL, 0);
    if (flag == -1) {

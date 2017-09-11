  /*! \brief close the connection */
  inline void Close(void) {
    if (sockfd != -1) {
#ifdef _WIN32
      closesocket(sockfd);
#else
	  close(sockfd);
#endif
	  sockfd = INVALID_SOCKET;
    } else {
      Error("TCPSocket::Close double close the socket or close without create");
    }

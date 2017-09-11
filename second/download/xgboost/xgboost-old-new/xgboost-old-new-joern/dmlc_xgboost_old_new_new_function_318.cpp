inline void Close(void) {
    if (sockfd != -1) {
      close(sockfd); sockfd = -1;
    } else {
      Error("TCPSocket::Close double close the socket or close without create");
    }
  }
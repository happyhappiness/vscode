  }
  // report an socket error
  inline static void Error(const char *msg) {
    int errsv = errno;
    utils::Error("Socket %s Error:%s", msg, strerror(errsv));
  }

 protected:
  explicit Socket(SOCKET sockfd) : sockfd(sockfd) {
  }
};

/*! 
 * \brief a wrapper of TCP socket that hopefully be cross platform
 */
class TCPSocket : public Socket{

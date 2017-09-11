  }
  // report an socket error
  inline static void Error(const char *msg) {
    int errsv = GetLastError();
#ifdef _WIN32
    utils::Error("Socket %s Error:WSAError-code=%d", msg, errsv);
#else
    utils::Error("Socket %s Error:%s", msg, strerror(errsv));
#endif
  }

 protected:
  explicit Socket(SOCKET sockfd) : sockfd(sockfd) {
  }
};

/*!
 * \brief a wrapper of TCP socket that hopefully be cross platform
 */
class TCPSocket : public Socket{

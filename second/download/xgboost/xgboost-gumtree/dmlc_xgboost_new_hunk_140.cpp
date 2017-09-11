    return sockfd;
  }
  /*!
   * \return last error of socket operation
   */
  inline static int GetLastError(void) {
#ifdef _WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
  }
  /*! \return whether last error was would block */
  inline static bool LastErrorWouldBlock(void) {
    int errsv = GetLastError();
#ifdef _WIN32
    return errsv == WSAEWOULDBLOCK;
#else
    return errsv == EAGAIN || errsv == EWOULDBLOCK;
#endif
  }
  /*!
   * \brief start up the socket module
   *   call this before using the sockets
   */

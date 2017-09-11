  // report an socket error
  inline static void SockError(const char *msg) {
    int errsv = errno;
    Error("Socket %s Error:%s", msg, strerror(errsv));
  }
};
/*! \brief helper data structure to perform select */

  // report an socket error
  inline static void SockError(const char *msg) {
    int errsv = errno;
    char buf[256];    
    Error("Socket %s Error:%s", msg, strerror_r(errsv, buf, sizeof(buf)));
  }
};
/*! \brief helper data structure to perform select */

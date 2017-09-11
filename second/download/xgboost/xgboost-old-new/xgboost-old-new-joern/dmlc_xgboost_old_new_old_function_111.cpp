inline static void Error(const char *msg) {
    int errsv = errno;
    utils::Error("Socket %s Error:%s", msg, strerror(errsv));
  }
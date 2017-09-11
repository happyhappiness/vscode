inline static void Error(const char *msg) {
    int errsv = GetLastError();
#ifdef _WIN32
    utils::Error("Socket %s Error:WSAError-code=%d", msg, errsv);
#else
    utils::Error("Socket %s Error:%s", msg, strerror(errsv));
#endif
  }
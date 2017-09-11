inline static int GetLastError(void) {
#ifdef _WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
  }
inline static ReturnType Errno2Return() {
    int errsv = utils::Socket::GetLastError();
    if (errsv == EAGAIN || errsv == EWOULDBLOCK || errsv == 0) return kSuccess;
#ifdef _WIN32
    if (errsv == WSAEWOULDBLOCK) return kSuccess;
    if (errsv == WSAECONNRESET) return kConnReset;
#endif
    if (errsv == ECONNRESET) return kConnReset;
    return kSockError;
  }
    const char *buf = reinterpret_cast<const char*>(buf_);
    size_t ndone = 0;
    while (ndone <  len) {
      ssize_t ret = send(sockfd, buf, len, 0);
      if (ret == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
        SockError("Recv", errno);

    char *buf = reinterpret_cast<char*>(buf_);
    size_t ndone = 0;
    while (ndone <  len) {
      ssize_t ret = recv(sockfd, buf, static_cast<sock_size_t>(len - ndone), MSG_WAITALL);
      if (ret == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
        SockError("Recv");

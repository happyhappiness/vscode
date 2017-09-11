    while (ndone <  len) {
      ssize_t ret = send(sockfd, buf, static_cast<ssize_t>(len - ndone), 0);
      if (ret == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
        Socket::Error("SendAll");
      }
      buf += ret;

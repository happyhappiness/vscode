    ssize_t ret = send(sockfd, buf, len, flag);
    if (ret == -1) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return 0;
      SockError("Send");
    }
    return ret;
  }  

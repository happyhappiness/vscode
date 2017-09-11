    ssize_t ret = recv(sockfd, buf, len, flags);
    if (ret == -1) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return 0;
      SockError("Recv");
    }
    return ret;
  } 

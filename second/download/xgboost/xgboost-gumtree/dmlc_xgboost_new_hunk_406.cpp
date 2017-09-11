#else
    int flag = fcntl(sockfd, F_GETFL, 0);
    if (flag == -1) {
      SockError("SetNonBlock-1");
    }
    if (non_block) {
      flag |= O_NONBLOCK;
    } else {
      flag &= ~O_NONBLOCK;
    }
    if (fcntl(sockfd, F_SETFL, flag) == -1) {
      SockError("SetNonBlock-2");
    }
#endif
  }

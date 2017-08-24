(errno == EAGAIN || errno == EWOULDBLOCK)
      return -EAGAIN;
    else
      return -errno;
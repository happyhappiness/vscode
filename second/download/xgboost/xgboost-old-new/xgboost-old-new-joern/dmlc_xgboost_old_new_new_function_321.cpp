inline int Select(long timeout = 0) {
    FD_ZERO(&read_set);
    FD_ZERO(&write_set);
    for (size_t i = 0; i < read_fds.size(); ++i) {
      FD_SET(read_fds[i], &read_set);
    } 
    for (size_t i = 0; i < write_fds.size(); ++i) {
      FD_SET(write_fds[i], &write_set);
    }
    int ret;
    if (timeout == 0) {
      ret = select(maxfd + 1, &read_set, &write_set, NULL, NULL);
    } else {
      timeval tm;
      tm.tv_usec = (timeout % 1000) * 1000;
      tm.tv_sec = timeout / 1000;
      ret = select(maxfd + 1, &read_set, &write_set, NULL, &tm);
    }
    if (ret == -1) {
      int errsv = errno;
      char buf[256];
      Error("Select Error: %s", strerror_r(errsv, buf, sizeof(buf)));      
    }
    return ret;
  }
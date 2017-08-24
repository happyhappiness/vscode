do {
      memset(&timeout, 0, sizeof timeout);
      r = port_getn(loop->fs_fd, &pe, 1, &n, &timeout);
    }
    while (r == -1 && errno == EINTR);